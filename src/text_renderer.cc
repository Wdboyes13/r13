#include <assets.h>
#include <r13.h>

#include <glad/gl.h>
#include <stb_truetype.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <stdexcept>
#include <utility>

void TextRND::init(R13* _prend) {
    prend = _prend;
    auto dimensions = prend->get_dimensions();

    shader = std::make_unique<Shader>(
        text_vert,
        text_vert_len,
        text_frag,
        text_frag_len);

    glm::mat4 projection = glm::ortho(0.0f, dimensions.x, 0.0f, dimensions.y);
    shader->use();
    glUniformMatrix4fv(glGetUniformLocation(shader->id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    init_font();
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRND::render(std::string text, Vec2 pos, float scale, Color color) {
    // activate corresponding render state
    shader->use();
    shader->set_vec4("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = characters[*c];

        float xpos = pos.x + ch.bearing.x * scale;
        float ypos = pos.y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;
        float vertices[6][4] = {
            { xpos, ypos + h, 0.0f, 0.0f },
            { xpos, ypos, 0.0f, 1.0f },
            { xpos + w, ypos, 1.0f, 1.0f },

            { xpos, ypos + h, 0.0f, 0.0f },
            { xpos + w, ypos, 1.0f, 1.0f },
            { xpos + w, ypos + h, 1.0f, 0.0f }
        };
        glBindTexture(GL_TEXTURE_2D, ch.texture_id);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        pos.x += (ch.advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec2 TextRND::measure(const std::string& text, float scale) {
    float width = 0.0f;
    float height = 0.0f;

    for (char c : text) {
        Character ch = characters[c];
        float h = ch.size.y * scale;
        width += (ch.advance >> 6) * scale;
        if (h > height) {
            height = h;
        }
    }

    return glm::vec2(width, height);
}

TextRND::~TextRND() {
    for (auto& [ch, character] : characters) {
        if (character.texture_id) {
            glDeleteTextures(1, &character.texture_id);
            character.texture_id = 0;
        }
    }
    characters.clear();
    if (vao) {
        glDeleteVertexArrays(1, &vao);
    }
    if (vbo) {
        glDeleteBuffers(1, &vbo);
    }
}

void TextRND::init_font() {
    const int font_size = 48;
    stbtt_fontinfo finfo;
    if (!stbtt_InitFont(&finfo, vt323_ttf, 0)) {
        throw std::runtime_error("Could not init stbtt font");
    }

    float scale = stbtt_ScaleForPixelHeight(&finfo, font_size);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        int adv, lsb;
        stbtt_GetCodepointHMetrics(&finfo, c, &adv, &lsb);

        int x0, y0, x1, y1;
        stbtt_GetCodepointBitmapBox(&finfo, c, scale, scale, &x0, &y0, &x1, &y1);

        int w = x1 - x0;
        int h = y1 - y0;

        unsigned int texture = 0;

        if (w > 0 && h > 0) {
            std::vector<unsigned char> bitmap(w * h, 0);
            stbtt_MakeCodepointBitmapSubpixel(
                &finfo,
                bitmap.data(),
                w,
                h,
                w,
                scale,
                scale,
                0,
                0,
                c);

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap.data());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        Character character = {
            texture,
            glm::ivec2(w, h),
            glm::ivec2(x0, -y0),
            (unsigned int)(adv * scale * 64)
        };
        characters.insert({ c, character });
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}
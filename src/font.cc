#define R13_PRIVATE_ACCESS

#include <assets.h>
#include <glad/gl.h>
#include <r13.h>
#include <stb_truetype.h>

#include <fstream>
#include <stdexcept>
#include <vector>

Font::Font(const std::string& path, int size) {
    std::vector<unsigned char> font_data;
    if (path == "__DEFAULT__") {
        font_data = std::vector<unsigned char>(vt323_ttf, vt323_ttf + vt323_ttf_len);
    } else {
        std::ifstream file(path, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Could not open font file");
        }

        font_data = std::vector<unsigned char>{
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>()
        };

        file.close();
    }

    stbtt_fontinfo finfo;
    if (!stbtt_InitFont(&finfo, font_data.data(), 0)) {
        throw std::runtime_error("Could not init stbtt font");
    }

    float scale = stbtt_ScaleForPixelHeight(&finfo, size);
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

        characters.insert({ (char)c, { .texture_id = texture, .size = Vec2<int>{ w, h }, .bearing = Vec2<int>{ x0, y0 }, .advance = (unsigned int)(adv * scale * 64) } });
    }
}

Vec2<float> Font::measure(const std::string& text, float scale) {
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

    return Vec2<float>{ width, height };
}

Font::~Font() {
    for (auto& [ch, character] : characters) {
        if (character.texture_id) {
            glDeleteTextures(1, &character.texture_id);
            character.texture_id = 0;
        }
    }
    characters.clear();
}
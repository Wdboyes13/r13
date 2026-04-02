#define R13_PRIVATE_ACCESS

#include <assets.h>
#include <r13.h>
#include <r13priv/classes.h>

#include <glad/gl.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

void SpriteRND::init(R13* _prend) {
    prend = _prend;
    ebo = 0;
    auto dimensions = prend->get_dimensions();
    shader = std::make_unique<Shader>(
        sprite_vert,
        sprite_vert_len,
        sprite_frag,
        sprite_frag_len);

    glm::mat4 projection = glm::ortho(0.0f, (float)dimensions.x, (float)dimensions.y, 0.0f);
    shader->use();
    glUniformMatrix4fv(glGetUniformLocation(shader->id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(glGetUniformLocation(shader->id, "sprite"), 0);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRND::render(Sprite& sprite, Vec2<float> pos, Vec2<float> scale) {
    float scaled_w = sprite.w * scale.x;
    float scaled_h = sprite.h * scale.y;

    float vertices[6][4] = {
        { pos.x, pos.y, 0.0f, 0.0f },                       // Top-left
        { pos.x, pos.y + scaled_h, 0.0f, 1.0f },            // Bottom-left
        { pos.x + scaled_w, pos.y + scaled_h, 1.0f, 1.0f }, // Bottom-right

        { pos.x, pos.y, 0.0f, 0.0f },                       // Top-left
        { pos.x + scaled_w, pos.y + scaled_h, 1.0f, 1.0f }, // Bottom-right
        { pos.x + scaled_w, pos.y, 1.0f, 0.0f }             // Top-right
    };

    shader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite.texture_id);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

SpriteRND::~SpriteRND() {
    if (vao) {
        glDeleteVertexArrays(1, &vao);
    }
    if (vbo) {
        glDeleteBuffers(1, &vbo);
    }
    if (ebo) {
        glDeleteBuffers(1, &ebo);
    }
}
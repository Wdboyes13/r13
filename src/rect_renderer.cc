#include <assets.h>
#include <r13.h>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

void SquareRND::init(R13* _prend) {
    prend = _prend;

    auto dimensions = prend->get_dimensions();

    shader = std::make_unique<Shader>(
        rect_vert,
        rect_vert_len,
        rect_frag,
        rect_frag_len);

    glm::mat4 projection = glm::ortho(0.0f, dimensions.x, 0.0f, dimensions.y);
    shader->use();
    glUniformMatrix4fv(glGetUniformLocation(shader->id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 2, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SquareRND::render(Rectangle rect, Color color) {
    shader->use();
    shader->set_vec4("color", color);

    glBindVertexArray(vao);

    float xpos = rect.x;
    float ypos = rect.y;
    float w = rect.width;
    float h = rect.height;

    float vertices[6][2] = {
        { xpos, ypos + h }, // Top-left
        { xpos, ypos },     // Bottom-left
        { xpos + w, ypos }, // Bottom-right

        { xpos, ypos + h },    // Top-left
        { xpos + w, ypos },    // Bottom-right
        { xpos + w, ypos + h } // Top-right
    };

    // Update vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

SquareRND::~SquareRND() {
    if (vao) {
        glDeleteVertexArrays(1, &vao);
    }
    if (vbo) {
        glDeleteBuffers(1, &vbo);
    }
}
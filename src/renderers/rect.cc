#define R13_PRIVATE_ACCESS

#include <r13.h>
#include <r13priv/classes.h>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

void RectRND::init(R13* _prend) {
    prend = _prend;

    auto dimensions = prend->get_dimensions();

    shader = std::make_unique<Shader>();

    glm::mat4 projection = glm::ortho(0.0f, (float)dimensions.x, (float)dimensions.y, 0.0f);
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

void RectRND::render(Rectangle rect, Color color) {
    shader->use();
    shader->set_vec4("color", color);

    glBindVertexArray(vao);

    float xpos = rect.x;
    float ypos = rect.y;
    float w = rect.width;
    float h = rect.height;

    float vertices[6][2] = {
        { xpos, ypos },         // Top-left
        { xpos, ypos + h },     // Bottom-left
        { xpos + w, ypos + h }, // Bottom-right

        { xpos, ypos },         // Top-left
        { xpos + w, ypos + h }, // Bottom-right
        { xpos + w, ypos }      // Top-right
    };

    // Update vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

RectRND::~RectRND() {
    if (vao) {
        glDeleteVertexArrays(1, &vao);
    }
    if (vbo) {
        glDeleteBuffers(1, &vbo);
    }
}
#define R13_PRIVATE_ACCESS
#include <assets.h>
#include <glad/gl.h>
#include <r13.h>
#include <r13priv/classes.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

void LineRND::init(R13* _prend) {
    prend = _prend;
    auto dimensions = prend->get_dimensions();

    shader = std::make_unique<Shader>(
        line_vert,
        line_vert_len,
        line_frag,
        line_frag_len);

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

void LineRND::render(Line line, Color color) {
    shader->use();
    shader->set_vec4("color", color);

    glBindVertexArray(vao);

    float vertices[2][2] = {
        { line.x1, line.y1 },
        { line.x2, line.y2 }
    };

    // Update vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_LINES, 0, 2);

    glBindVertexArray(0);
}

LineRND::~LineRND() {
    if (vao) {
        glDeleteVertexArrays(1, &vao);
    }
    if (vbo) {
        glDeleteBuffers(1, &vbo);
    }
}
#define R13_PRIVATE_ACCESS

#include <r13.h>
#include <r13priv/classes.h>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

void PolyRND::init(R13* _prend) {
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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void PolyRND::render(int nv, float radius, Vec2<float> pos, Color color) {
    shader->use();
    shader->set_vec4("color", color);

    glBindVertexArray(vao);

    std::vector<float> vertices;
    if (nv < 3) {
        return;
    }

    vertices.push_back(pos.x);
    vertices.push_back(pos.y);

    const float angle_mul = 2.0f * M_PI;
    const float angle_stp = angle_mul / nv;
    for (int i = nv; i >= 0; i--) {
        const float x = radius * cos(i * angle_stp - angle_mul);
        const float y = radius * sin(i * angle_stp - angle_mul);
        vertices.push_back(x + pos.x);
        vertices.push_back(y + pos.y);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);
    glBindVertexArray(0);
}

PolyRND::~PolyRND() {
    if (vao) {
        glDeleteVertexArrays(1, &vao);
    }
    if (vbo) {
        glDeleteBuffers(1, &vbo);
    }
}
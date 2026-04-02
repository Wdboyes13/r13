#define R13_PRIVATE_ACCESS

#include <assets.h>
#include <r13.h>
#include <r13priv/classes.h>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

void CircleRND::init(R13* _prend) {
    prend = _prend;
    auto dimensions = prend->get_dimensions();

    shader = std::make_unique<Shader>(
        circle_vert,
        circle_vert_len,
        circle_frag,
        circle_frag_len);

    glm::mat4 projection = glm::ortho(0.0f, (float)dimensions.x, (float)dimensions.y, 0.0f);
    shader->use();
    glUniformMatrix4fv(glGetUniformLocation(shader->id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CircleRND::render(Vec2<float> center, float radius, Color color) {
    shader->use();
    shader->set_vec4("color", color);

    glBindVertexArray(vao);

    // Create a quad around the circle
    float xpos = center.x - radius;
    float ypos = center.y - radius;
    float w = radius * 2.0f;
    float h = radius * 2.0f;

    // Vertices with texture coordinates for the fragment shader
    // Format: [x, y, texCoordX, texCoordY]
    float vertices[6][4] = {
        { xpos, ypos, -1.0f, -1.0f },       // Top-left
        { xpos, ypos + h, -1.0f, 1.0f },    // Bottom-left
        { xpos + w, ypos + h, 1.0f, 1.0f }, // Bottom-right
        { xpos, ypos, -1.0f, -1.0f },       // Top-left
        { xpos + w, ypos + h, 1.0f, 1.0f }, // Bottom-right
        { xpos + w, ypos, 1.0f, -1.0f }     // Top-right
    };

    // Update VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

CircleRND::~CircleRND() {
    if (vao) {
        glDeleteVertexArrays(1, &vao);
    }
    if (vbo) {
        glDeleteBuffers(1, &vbo);
    }
}
#include <r13.h>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <string>

std::string Shader::data_to_string(unsigned char* data, unsigned int len) {
    return std::string(reinterpret_cast<const char*>(data), len);
}

GLuint Shader::compile_shader(const char* source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, NULL, log);
        throw std::runtime_error(log);
    }
    return shader;
}

Shader::Shader(unsigned char* vert_data, unsigned int vert_data_len, unsigned char* frag_data, unsigned int frag_data_len) {
    auto frag = compile_shader(data_to_string(frag_data, frag_data_len).c_str(), GL_FRAGMENT_SHADER);
    auto vert = compile_shader(data_to_string(vert_data, vert_data_len).c_str(), GL_VERTEX_SHADER);

    id = glCreateProgram();
    glAttachShader(id, frag);
    glAttachShader(id, vert);
    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetProgramInfoLog(id, 1024, NULL, log);
        throw std::runtime_error(log);
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
}

Shader::~Shader() {
    if (id) {
        glDeleteProgram(id);
    }
}

void Shader::use() { glUseProgram(id); }

void Shader::set_vec2(const char* name, Vec2 v) {
    glUniform2f(glGetUniformLocation(id, name), v.x, v.y);
}
void Shader::set_vec3(const char* name, Vec3 v) {
    glUniform3f(glGetUniformLocation(id, name), v.x, v.y, v.z);
}

void Shader::set_vec4(const char* name, Vec4 v) {
    glUniform4f(glGetUniformLocation(id, name), v.x, v.y, v.z, v.w);
}

void Shader::set_float(const char* name, float v) {
    glUniform1f(glGetUniformLocation(id, name), v);
}
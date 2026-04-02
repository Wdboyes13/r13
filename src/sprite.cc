#include <glad/gl.h>
#include <r13.h>
#include <stb_image.h>

Sprite::Sprite(const std::string& path) {
    data = stbi_load(path.c_str(), &w, &h, &c, 0);
    if (!data) {
        throw std::runtime_error("failed to load image through STBI");
    }
    glGenTextures(1, &texture_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint format = GL_RGB;
    if (c == 1) {
        format = GL_RED;
    } else if (c == 4) {
        format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
}

Sprite::~Sprite() {
    if (data) {
        stbi_image_free(data);
    }

    if (texture_id) {
        glDeleteTextures(1, &texture_id);
    }
}
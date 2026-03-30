#include <r13.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

Vec2<int> R13::get_dimensions() {
    return Vec2<int>{ width, height };
}

void R13::begin_draw(Color c) {
    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT);
    frame_times.push_back(glfwGetTime() * 1000);
}

void R13::end_draw() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool R13::should_close() {
    return glfwWindowShouldClose(window);
}

void R13::set_window_icon(const std::string& path, int height, int width) {
    auto stbi = stbi_load(path.c_str(), &width, &height, nullptr, 4);
    if (!stbi) {
        throw std::runtime_error("Could not load window icon");
    }

    GLFWimage icon{
        .width = width,
        .height = height,
        .pixels = stbi
    };
    glfwSetWindowIcon(window, 1, &icon);
    stbi_image_free(stbi);
}

void R13::set_window_title(const std::string& title) {
    glfwSetWindowTitle(window, title.c_str());
}

void R13::set_window_pos(Vec2<int> size) {
    glfwSetWindowPos(window, size.x, size.y);
}

void R13::set_window_opacity(float opacity) {
    glfwSetWindowOpacity(window, opacity);
}

void R13::set_window_size(Vec2<int> size) {
    glfwSetWindowSize(window, size.x, size.y);
}

void R13::set_window_fullscreen() {
    auto monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}
#include <r13.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

Vec2 R13::get_dimensions() {
    return Vec2{ (float)width, (float)height };
}

void R13::fb_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void R13::begin_draw(Color c) {
    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void R13::end_draw() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool R13::is_key_down(int k) {
    return glfwGetKey(window, k) == GLFW_PRESS;
}

bool R13::should_close() {
    return glfwWindowShouldClose(window);
}

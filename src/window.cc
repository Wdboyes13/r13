#include <r13.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

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

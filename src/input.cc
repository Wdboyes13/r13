#include <GLFW/glfw3.h>
#include <r13.h>

bool R13::is_key_down(int k) {
    return glfwGetKey(window, k) == GLFW_PRESS;
}

bool R13::is_mouse_button_down(int b) {
    return glfwGetMouseButton(window, b) == GLFW_PRESS;
}

Vec2<double> R13::get_mouse_pos() {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return Vec2<double>{ x, y };
}

void R13::set_key_callback(R13::KeyCallback kb) {
    glfwSetKeyCallback(window, kb);
}
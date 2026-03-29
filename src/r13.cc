#include <r13.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <string>

R13::R13(const std::string& _data_path, int width, int height)
    : data_path(_data_path), width(width), height(height) { this->init(); }

R13::~R13() {
    glfwTerminate();
}

glm::vec2 R13::get_dimensions() {
    return glm::vec2(width, height);
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

void R13::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, "test", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, fb_size_callback);

    if (!gladLoadGL(glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    rect = std::make_unique<SquareRND>();
    text = std::make_unique<TextRND>();
    circle = std::make_unique<CircleRND>();

    rect->init(this);
    text->init(this);
    circle->init(this);
}
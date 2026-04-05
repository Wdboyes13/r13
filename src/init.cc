#define R13_PRIVATE_ACCESS

#include <r13.h>
#include <r13priv/classes.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

R13::R13(const int width, const int height, const int font_size)
    : font_sz(font_size), width(width), height(height) { this->init(); }

R13::~R13() {
    glfwTerminate();
}

static void fb_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
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

    rect = std::make_unique<RectRND>();
    text = std::make_unique<TextRND>(font_sz);
    circle = std::make_unique<CircleRND>();
    line = std::make_unique<LineRND>();
    sprite = std::make_unique<SpriteRND>();
    polygon = std::make_unique<PolyRND>();

    rect->init(this);
    text->init(this);
    circle->init(this);
    line->init(this);
    sprite->init(this);
    polygon->init(this);

    audio = std::make_unique<AudioPlayer>();

    rng = std::mt19937_64(std::random_device{}());
}
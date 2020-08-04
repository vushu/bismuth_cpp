#include <bismuth/shader.hpp>
#include <bismuth/logging.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bismuth/renderer.hpp>
#include <glm/vec4.hpp>
#include <stdexcept>
using namespace bi;

Renderer::~Renderer() {}

void Renderer::init() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        bi::log("Renderer: Failed to initialize GLAD");
        throw std::runtime_error("Renderer: Failed to initialize GLAD");
    }
}

void Renderer::clear(glm::vec4 color) {
    clear(color.x, color.y, color.z, color.w);
}

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}



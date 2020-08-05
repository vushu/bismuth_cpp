#define GLFW_INCLUDE_NONE
#include <bismuth/logging.hpp>
#include <GLFW/glfw3.h>
#include <bismuth/application.hpp>
#include <memory>
#include <glm/glm.hpp>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

using namespace bi;

Application::Application() {
    construct(800, 600, "Bismuth");
}

Application::Application(int width, int height, std::string title) {
    construct(width, height, title);
}

void Application::construct(int width, int height, std::string title) {
    this->title = title;
    this->window = std::make_unique<Window>(width, height, title);
    this->renderer = std::make_unique<Renderer>(this->window, this->camera);
}

Application::~Application() {
    log("Application: " + this->title + " is now destroyed");
}

void Application::run() {
    log("Running Application: " + title);
    applicationInit();
    init();
#ifdef __EMSCRIPTEN__
    beginTime = glfwGetTime();
    endTime = glfwGetTime();
    dt = -1.0f;
#else
    loop();
#endif

}

void Application::update(float dt) { }
void Application::init() { }

void Application::emLoop() {
    window->pollEvents();
    if (dt >= 0) {
        update(dt);
        renderer->clear(glm::vec4(0.7f, 0.0f, 0.5f, 1.0f));
    }
    window->swapBuffers();
    endTime = glfwGetTime();
    dt = endTime - beginTime;
    beginTime = endTime;
}

void Application::loop() {
    float beginTime = glfwGetTime();
    float endTime = glfwGetTime();
    float dt = -1.0f;

    while (!window->windowShouldClose()) {
        window->pollEvents();

        if (dt >= 0) {
            update(dt);
            renderer->clear(glm::vec4(0.7f, 0.0f, 0.5f, 1.0f));
        }

        window->swapBuffers();
        endTime = glfwGetTime();
        dt = endTime - beginTime;
        beginTime = endTime;
    }

}

void Application::applicationInit() {
    log("Application: init");
    this->window->init();
    this->renderer->init();
}


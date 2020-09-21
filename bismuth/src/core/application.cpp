#include "bismuth/renderer.hpp"
#include <exception>
//#include <imgui_impl_opengl3.h>
//#include <imgui.h>
//#include <imgui_impl_glfw.h>
#define GLFW_INCLUDE_NONE
//#include <bismuth/textrenderer.hpp>
#include <bismuth/logging.hpp>
#include <GLFW/glfw3.h>
#include <bismuth/application.hpp>
#include <bismuth/guimanager.hpp>
#include <memory>
#include <glm/glm.hpp>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif


using namespace bi;

Application::Application() {
    construct({800, 600}, {}, "Bismuth");
}

Application::Application(int width, int height, std::string title) {
    construct({width, height}, {}, title);
}

Application::Application(glm::vec2 resolution, glm::vec4 tileInfo, std::string title) {
    construct(resolution, tileInfo, title);
}

void Application::construct(glm::vec2 resolution, glm::vec4 tileInfo, std::string title) {

    this->ioManager = std::make_shared<IOManager>(resolution, tileInfo, title);
    this->scenemanager = std::make_unique<SceneManager>(this->ioManager);
    this->title = title;
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
    dt = 1.0f/60.0f;
    //dt = -1.0f;
#else
    nativeLoop();
#endif

}

void Application::update(float dt) { }
void Application::init() { }

void Application::loop() {
    this->ioManager->window->pollEvents();

    update(dt);

    this->scenemanager->update(dt);

    this->ioManager->window->swapBuffers();

    endTime = glfwGetTime();
    dt = endTime - beginTime;
    beginTime = endTime;
}

void Application::nativeLoop() {
    beginTime = glfwGetTime();
    endTime = glfwGetTime();
    dt = 1.0f/60.0f;
    while (!this->ioManager->window->windowShouldClose()) {
        loop();
    }

}

void Application::initOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        log("Renderer: Failed to initialize GLAD");
        throw std::runtime_error("Renderer: Failed to initialize GLAD");
    }
    // alpha blending
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);


}

void Application::applicationInit() {
    log("Application: init");
    this->ioManager->window->init();
    initOpenGL();
    this->ioManager->renderer->init();
    this->ioManager->shaperenderer->init();
}



Renderer& Application::getRenderer() {
    return *this->ioManager->renderer;
}

ShapeRenderer& Application::getShapeRenderer() {
    return *this->ioManager->shaperenderer;
}

Window& Application::getWindow() {
    return *this->ioManager->window;
}

Camera& Application::getCamera() {
    return *this->ioManager->camera;
}

AudioManager& Application::getAudioManager() {
    return *this->ioManager->audioManager;
}

AssetManager& Application::getAssetManager() {
    return *this->ioManager->assetmanager;
}

GuiManager& Application::getGuiManager() {
    return *this->ioManager->guimanager;
}

Framebuffer& Application::getMainFramebuffer() {
    return *this->ioManager->mainFramebuffer;
}

SceneManager& Application::getSceneManager() {
    return *this->scenemanager;
}

IOManager& Application::getIOManager(){
    return *this->ioManager;
}



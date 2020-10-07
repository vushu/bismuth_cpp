#include "bismuth/assetmanager.hpp"
#include "bismuth/iomanager.hpp"
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

Application::Application(std::string title) {
    construct({0,0}, {}, title);
}

Application::Application(glm::vec4 tileInfo,std::string title) {
    construct({0,0}, tileInfo, title);
}
Application::Application(int width, int height, std::string title) {
    construct({width, height}, {}, title);
}

Application::Application(glm::vec2 resolution, glm::vec4 tileInfo, std::string title) {
    construct(resolution, tileInfo, title);
}

void Application::construct(glm::vec2 resolution, glm::vec4 tileInfo, std::string title) {

    getIOManager().construct(resolution, tileInfo, title);
    this->scenemanager = std::make_unique<SceneManager>();
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

    getWindow().pollEvents();

    getRenderer().resetStats();
    update(dt);

    this->scenemanager->update(dt);

    getWindow().swapBuffers();

    endTime = glfwGetTime();
    dt = endTime - beginTime;
    beginTime = endTime;
}

void Application::fixedLoop() {
    getWindow().pollEvents();

    dt = endTime - beginTime;
    beginTime = endTime;
    accumulated += dt;

    while(accumulated > FRAMES_PER_SEC) {
        update(1.0f);
        this->scenemanager->update(dt);
        accumulated -= FRAMES_PER_SEC;
        accumulated = std::max(0.0f, accumulated);
    }

    getWindow().swapBuffers();
}

void Application::nativeLoop() {
    beginTime = glfwGetTime();
    endTime = glfwGetTime();
    dt = 1.0f/60.0f;
    while (!getWindow().windowShouldClose()) {
        loop();
        //fixedLoop();
    }
    getWindow().destroy();

}


void Application::initOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        log("Renderer: Failed to initialize GLAD");
        throw std::runtime_error("Renderer: Failed to initialize GLAD");
    }
    // alpha blending
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    //stencil buffer
    glEnable(GL_STENCIL_TEST);

}

void Application::applicationInit() {
    log("Application: init");
    getWindow().init();
    initOpenGL();
    getRenderer().init();
    getShapeRenderer().init();
    //getGuiManager().init();
}

Renderer& Application::getRenderer() {
    return *bi::ioManager().renderer;
}

ShapeRenderer& Application::getShapeRenderer() {
    return *bi::ioManager().shaperenderer;
}

Window& Application::getWindow() {
    return *bi::ioManager().window;
}

Camera& Application::getCamera() {
    return *bi::ioManager().camera;
}

AudioManager& Application::getAudioManager() {
    return *bi::ioManager().audioManager;
}

AssetManager& Application::getAssetManager() {
    return *bi::ioManager().assetmanager;
}

GuiManager& Application::getGuiManager() {
    return *bi::ioManager().guimanager;
}

Framebuffer& Application::getMainFramebuffer() {
    return *bi::ioManager().mainFramebuffer;
}

SceneManager& Application::getSceneManager() {
    return *this->scenemanager;
}

IOManager& Application::getIOManager(){
    return bi::ioManager();
}



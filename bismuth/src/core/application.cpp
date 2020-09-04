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
    construct(800, 600, "Bismuth");
}

Application::Application(int width, int height, std::string title) {
    construct(width, height, title);
}

void Application::construct(int width, int height, std::string title) {
    this->title = title;
    this->window = std::make_unique<Window>(width, height, title);
    this->camera = std::make_unique<Camera>();
    this->assetmanager = std::make_unique<AssetManager>();
    //this->renderer = std::make_unique<Renderer>(this->window, this->camera, *this->assetmanager);
    this->audioManager = std::make_unique<AudioManager>();
    this->guimanager = std::make_unique<GuiManager>(this->getWindow());
    //this->textrenderer = std::make_unique<TextRenderer>();
    this->renderer = std::make_unique<Renderer>(*this->camera);
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
    window->pollEvents();
    //if (dt >= 0) {
    //renderer->render(dt);
    renderer->clear(glm::vec4(0.30f, 0.30f, 0.30f, 1.0f));
    update(dt);
    //}
    window->swapBuffers();
    endTime = glfwGetTime();
    dt = endTime - beginTime;
    beginTime = endTime;
}

void Application::nativeLoop() {

    //const float FRAME_DURATION = 1.0f/60.0f;

    beginTime = glfwGetTime();
    endTime = glfwGetTime();
    //float dt = -1.0f;
    dt = 1.0f/60.0f;
    //float accumulator = 0;
    //float lastFrameTime = 0.0f;
    //float lastUpdateTime = 0.0f;
    while (!window->windowShouldClose()) {
        loop();
    }

}

void Application::initOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        log("Renderer: Failed to initialize GLAD");
        throw std::runtime_error("Renderer: Failed to initialize GLAD");
    }
    //font
    //glEnable(GL_CULL_FACE);
    // alpha blending
    //glBlendFunc(GL_SRC1_COLOR, GL_ONE_MINUS_SRC1_COLOR);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    //glfwWindowHint(GLFW_SAMPLES, 4);
    //glEnable(GL_MULTISAMPLE);


}

void Application::applicationInit() {
    log("Application: init");
    this->window->init();
    initOpenGL();
    this->renderer->init();

    //self init
    //this->textrenderer->init();
    //this->guimanager->init();
    //this->audioManager->init();
}



Renderer& Application::getRenderer() {
    return *this->renderer;
}

Window& Application::getWindow() {
    return *this->window;
}

Camera& Application::getCamera() {
    return *this->camera;
}

AudioManager& Application::getAudioManager() {
    return *this->audioManager;
}

AssetManager& Application::getAssetManager() {
    return *this->assetmanager;
}

GuiManager& Application::getGuiManager() {
    return *this->guimanager;
}






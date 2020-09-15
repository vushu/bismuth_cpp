#include <bismuth/scene.hpp>
using namespace bi;

Scene::Scene() { }

Scene::~Scene() { }

void Scene::sceneInit(std::shared_ptr<IOManager> iomanager) {
    this->ioManager = iomanager;
}

void Scene::init() {}
void Scene::sceneStart() {
    if (!started) {
        start();
        started = true;
    }
}
void Scene::start() {}
void Scene::close() {}
void Scene::update(float dt) {}

Renderer& Scene::getRenderer() {
    return *this->ioManager->renderer;
}

ShapeRenderer& Scene::getShapeRenderer() {
    return *this->ioManager->shaperenderer;
}

Window& Scene::getWindow() {
    return *this->ioManager->window;
}

Camera& Scene::getCamera() {
    return *this->ioManager->camera;
}

GuiManager& Scene::getGuiManager() {
    return *this->ioManager->guimanager;
}

AudioManager& Scene::getAudioManager() {
    return *this->ioManager->audioManager;
}

AssetManager& Scene::getAssetManager() {
    return *this->ioManager->assetmanager;
}


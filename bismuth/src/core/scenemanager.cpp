#include <bismuth/scenemanager.hpp>
using namespace bi;

SceneManager::~SceneManager() {

}

void SceneManager::addScene(std::string name, std::unique_ptr<Scene> scene) {
    scenes.emplace(name, std::move(scene));
    this->currentScene = name;
}
void SceneManager::setScene(std::string name) {
    this->currentScene = name;
}

void SceneManager::update(float dt) {

    if (scenes.count(currentScene) > 0) {
        scenes.at(currentScene)->update(dt);
    }
}

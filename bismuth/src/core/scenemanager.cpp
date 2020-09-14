#include <bismuth/scenemanager.hpp>
using namespace bi;

SceneManager::~SceneManager() {

}

void SceneManager::createScene(std::string name) {
    scenes.emplace(name, std::make_unique<Scene>());
}

void SceneManager::update(float dt) {
    for(auto& scene : scenes) {
        scene.second->update(dt);
    }
}

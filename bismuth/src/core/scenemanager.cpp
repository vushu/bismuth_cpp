#include "bismuth/logging.hpp"
#include <bismuth/scenemanager.hpp>

using namespace bi;

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {
    bi::log("Destroying scenemanager");
}

void SceneManager::addScene(std::string name, std::unique_ptr<Scene> scene) {
    scene->sceneInit();
    scene->init();
    scenes.emplace(name, std::move(scene));
    if (currentScene == "")
        setScene(name);
}

void SceneManager::setScene(std::string name) {
    if (scenes.count(name) > 0)
        this->currentScene = name;
}

void SceneManager::update(float dt) {

    if (scenes.count(currentScene) > 0) {
        scenes.at(currentScene)->sceneStart();
        scenes.at(currentScene)->update(dt);

        std::string nextScene = scenes.at(currentScene)->nextScene;

        if (!nextScene.empty() && scenes.count(nextScene) > 0) {
            bi::log("nextScene:", nextScene);
            scenes.at(currentScene)->nextScene = "";
            scenes.at(currentScene)->started = false;
            scenes.at(currentScene)->close();
            setScene(nextScene);
        }
    }
}

void SceneManager::render(float dt) {
    if (scenes.count(currentScene) > 0)
        scenes.at(currentScene)->render(dt);
}

void SceneManager::processInput(float dt) {
    if (scenes.count(currentScene) > 0)
        scenes.at(currentScene)->processInput(dt);
}

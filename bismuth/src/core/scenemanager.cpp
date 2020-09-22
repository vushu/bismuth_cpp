#include <bismuth/scenemanager.hpp>
using namespace bi;

SceneManager::~SceneManager() {

}

void SceneManager::addScene(std::string name, std::unique_ptr<Scene> scene) {
    scene->sceneInit(ioManager);
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

        //this->ioManager->renderer->clear(glm::vec4(0.30f, 0.30f, 0.30f, 1.0f));

        scenes.at(currentScene)->sceneStart();
        scenes.at(currentScene)->update(dt);

        std::string nextScene = scenes.at(currentScene)->nextScene;

        if (nextScene != "") {
            scenes.at(currentScene)->nextScene = "";
            scenes.at(currentScene)->started = false;
            scenes.at(currentScene)->close();
            setScene(nextScene);
        }
    }
}

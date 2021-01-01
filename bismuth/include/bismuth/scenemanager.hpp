#pragma once

#include <string>
#include <memory>
#include <map>
#include <bismuth/scene.hpp>
#include <bismuth/iomanager.hpp>

namespace bi {

    class SceneManager {
    public:
        // constructors, asssignment, destructor
        SceneManager();

        ~SceneManager();

        void addScene(std::string name, std::unique_ptr<Scene> scene);

        void setScene(std::string name);

        void processInput(float dt);

        void update(float dt);

        void render(float dt);


    private:
        std::string currentScene = "";
        std::map<std::string, std::unique_ptr<Scene>> scenes;
        //std::shared_ptr<IOManager> ioManager;
    };
}

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
            SceneManager(IOManager& iomanager) : ioManager(iomanager) {}

            ~SceneManager();
            void addScene(std::string name, std::unique_ptr<Scene> scene);
            void setScene(std::string name);
            void update(float dt);

        private:
            std::string currentScene;
            std::map<std::string, std::unique_ptr<Scene>> scenes;
            IOManager& ioManager;


    };
}

#pragma once
#include "bismuth/sound.hpp"
#include "tmxlite/Tileset.hpp"
#include <bismuth/scene.hpp>
#include <vector>
class FirstScene : public bi::Scene {
    public:
        // constructors, asssignment, destructor
        FirstScene();
        ~FirstScene();
        void init();
        void update(float dt);
        void close();
        void start();
    private:
        std::shared_ptr<bi::Sound> levelSound;
        std::vector<glm::vec2> tiles;
        std::map<int, std::vector<glm::vec2>> layers;
        //tmx::Tileset mTileset = nullptr;

};

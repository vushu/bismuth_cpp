#pragma once
#include "bismuth/sound.hpp"
#include <bismuth/tile.hpp>
#include "tmxlite/Tileset.hpp"
#include <bismuth/scene.hpp>
#include <bismuth/tiledmap.hpp>
#include "playersystem.hpp"
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
        std::vector<bi::Tile> tiles;
        std::map<int, std::vector<glm::vec2>> layers;
        unsigned int texId;
        PlayerSystem playersystem;
        std::string tilemapPath = "resources/assets/tiles/level1.tmx";
        std::string smokeImage = "resources/assets/images/smoke.png";
        unsigned smokeTexId;

};

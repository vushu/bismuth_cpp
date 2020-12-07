#pragma once
#include "bismuth/font.hpp"
#include "bismuth/sound.hpp"
#include "../systems/playersystem.hpp"
#include "tmxlite/Tileset.hpp"
#include <bismuth/animatedsprite.hpp>
#include <bismuth/animation.hpp>
#include <bismuth/scene.hpp>
#include <bismuth/tile.hpp>
#include <bismuth/tiledmap.hpp>
#include <vector>
//#include <nanovg/nanovg.h>
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
    //NVGcontext* vg = nullptr;
    bi::AnimatedSprite animatedSprite;
    std::unique_ptr<bi::Animation> anim;
    std::shared_ptr<bi::Sound> levelSound;
    std::vector<bi::Tile> tiles;
    std::map<int, std::vector<glm::vec2>> layers;
    unsigned int texId;
    PlayerSystem playersystem;
    std::string tilemapPath = "resources/assets/tiles/level1.tmx";
    std::string smokeImage = "resources/assets/images/smoke.png";
    std::string drillPath = "resources/assets/images/drill.png";
    unsigned smokeTexId;
    unsigned drillTexId;
    bool showGrid = false;
    std::unique_ptr<bi::Font> font;
};

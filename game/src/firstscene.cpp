#include "firstscene.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

FirstScene::FirstScene() {}

FirstScene::~FirstScene() {}

void FirstScene::start() {
    //levelSound->playSound();
}
void FirstScene::init() {
    this->levelSound = std::make_shared<bi::Sound>("resources/assets/audio/Soliloquy.mp3");
    levelSound->init();
    levelSound->setLoop(true);

    getAudioManager().addSound(levelSound);

    //Loading tmx
    tmx::Map map;
    if (map.load("resources/assets/tiles/level1.tmx")) {
        const auto& layers = map.getLayers();

        bi::log("map size x", (int)map.getTileSize().x);
        bi::log("map size y", (int)map.getTileSize().y);

        const auto& tileSize = map.getTileSize();
        const auto& tilesets = map.getTilesets();
        for (const auto& tileset : tilesets) {
            //bi::log("tilesetPath", tileset.getImagePath());
            int texId = getAssetManager().loadTexture(tileset.getImagePath());
            bi::log("imgX", std::to_string(tileset.getImageSize().x));
            bi::log("imgY", std::to_string(tileset.getImageSize().y));
            //mTileset = tileset;
            //bi::log("texId", texId);

        }

        int layerIndex = 0;
        for (const auto& layer : layers) {
            // if object
            if (layer->getType() == tmx::Layer::Type::Object) {

            }

            else if (layer->getType() == tmx::Layer::Type::Tile) {
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
                //std::vector<glm::vec2> tiles;
                //bi::log("Mapsize");
                //
                int tilePosX = 0;
                int tilePosY = 0;
                int sizeX = tileLayer.getSize().x; //* tileSize.x; //x: 30 * 16 =  480
                int sizeY = tileLayer.getSize().y;// * tileSize.y; //y: 17 * 16 = 272
                int layerSizeX = sizeX * tileSize.x;
                int layerSizeY = sizeY * tileSize.x;

                int index = 0;
                for (const auto& tile : tileLayer.getTiles()) {
                    tilePosX = index % sizeX;
                    if (index % sizeX == 0 && index > 0){
                        tilePosY++;
                    }
                    glm::vec2 pos = {tilePosX * tileSize.x, tilePosY * tileSize.y};
                    //std::array<glm::vec2, 4> defaultTexcoords = {
                    //glm::vec2(1.0f, 1.0f), //br
                    //glm::vec2(1.0f, 0.0f), //tr
                    //glm::vec2(0.0f, 0.0f), //tl
                    //glm::vec2(0.0f, 1.0f) //bl
                    //};
                    tiles.push_back(pos);
                    index++;
                }
                //layers.emplace(layerIndex, tiles);
            }
        }
    }
}



void FirstScene::update(float dt) {
    if (bi::keyInput().isKeyPressed(GLFW_KEY_F)) {
        getWindow().fullscreen(getWindow().width, getWindow().height);
    }

    for(const auto& pos : tiles) {
        getRenderer().drawTexture(pos, {16,16}, {1,1,1,1}, 1, 0);
    }

    getRenderer().endFlushBegin();

    getGuiManager().beginDraw();
    getGuiManager().showFPS();
    getGuiManager().endDraw();

}

void FirstScene::close() {
    levelSound->stopSound();
}

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
    levelSound->playSound();
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
        glm::vec2 imageSize;

        for (const auto& tileset : tilesets) {
            //bi::log("tilesetPath", tileset.getImagePath());
            texId = getAssetManager().loadTexture(tileset.getImagePath());
            bi::log("imgX", std::to_string(tileset.getImageSize().x));
            bi::log("imgY", std::to_string(tileset.getImageSize().y));
            imageSize = {tileset.getImageSize().x, tileset.getImageSize().y};
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

                int index = 0;
                for (const auto& tile : tileLayer.getTiles()) {
                    tilePosX = index % sizeX;
                    tilePosY = (int) index / sizeX;

                    glm::vec2 pos = {tilePosX * tileSize.x, tilePosY * tileSize.y};
                    bi::Tile t(tile.ID, texId, imageSize, pos, {tileSize.x, tileSize.y });
                    tiles.push_back(t);
                    index++;
                }
            }
        }
    }
}



void FirstScene::update(float dt) {
    if (bi::keyInput().isKeyPressed(GLFW_KEY_F)) {
        getWindow().fullscreen(getWindow().width, getWindow().height);
    }

    for(bi::Tile& tile : tiles) {
        //bi::log("TileID: ", (int) tile.getId());
        getRenderer().drawTexture(tile.getPosition(), tile.getTileSize(), {1,1,1,1}, tile.getTextureId(), 0, tile.getTexCoords());
    }

    getRenderer().endFlushBegin();

    getGuiManager().beginDraw();
    getGuiManager().showFPS();
    getGuiManager().endDraw();

}

void FirstScene::close() {
    levelSound->stopSound();
}

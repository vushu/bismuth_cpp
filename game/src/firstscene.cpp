#include "firstscene.hpp"
#include "bismuth/logging.hpp"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
FirstScene::FirstScene() {

}

FirstScene::~FirstScene() {

}

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

        for (const auto& layer : layers) {
            // if object
            if (layer->getType() == tmx::Layer::Type::Object) {

            }
            else if (layer->getType() == tmx::Layer::Type::Tile) {
                const auto& tileLayer = layer ->getLayerAs<tmx::TileLayer>();
                bi::log("Mapsize");
                bi::log(std::to_string(tileLayer.getSize().x));
                bi::log(std::to_string(tileLayer.getSize().y));
                for (const auto& tile : tileLayer.getTiles()) {

                    bi::log("Tilesize");
                    bi::log(std::to_string(tile.ID));
                }
            }
        }

        const auto& tilesets = map.getTilesets();
        for (const auto& tileset : tilesets) {
            bi::log("tilesetPath", tileset.getImagePath());
            int  texId = getAssetManager().loadTexture(tileset.getImagePath());
            bi::log("texId", texId);
        }

    }
}


void FirstScene::update(float dt) {

    getGuiManager().beginDraw();
    getGuiManager().showFPS();
    getGuiManager().endDraw();

}

void FirstScene::close() {
    levelSound->stopSound();
}

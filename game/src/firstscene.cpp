#include "firstscene.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/mouselistener.hpp"
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
    getTileManager().loadTileMap(tilemapPath);
}

void FirstScene::update(float dt) {
    if (bi::keyInput().isKeyPressed(GLFW_KEY_F)) {
        getWindow().fullscreen(getWindow().width, getWindow().height);
    }
    if (bi::mouseInput().isDragging) {
        float x = bi::mouseInput().toOrthoX(getCamera(), getWindow().width);
        bi::log("Mouse x:",std::to_string(x));

        float y = bi::mouseInput().toOrthoY(getCamera(), getWindow().height);

        bi::log("Mouse y:",std::to_string(y));
    }
    getTileManager().draw(tilemapPath, 0, getRenderer());

    getRenderer().endFlushBegin();

    getGuiManager().beginDraw();
    getGuiManager().showFPS();
    getGuiManager().endDraw();

}

void FirstScene::close() {
    levelSound->stopSound();
}

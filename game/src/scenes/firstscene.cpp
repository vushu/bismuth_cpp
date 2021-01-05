#include "firstscene.hpp"
#include "../systems/objectsystem.hpp"
#include "bismuth/keylistener.hpp"
#include <bismuth/animation.hpp>
#include <bismuth/logging.hpp>
#include <memory>
#include <tmxlite/Layer.hpp>

FirstScene::FirstScene() {}

FirstScene::~FirstScene() {

    //nvgDeleteGLES3(vg);
}

void FirstScene::start() {
    //levelSound->playSound();
}

void FirstScene::init() {
    getGuiManager().init();
    font = std::make_unique<bi::Font>();
    font->loadFnt("resources/assets/fonts/manjaru.fnt");

    this->levelSound = std::make_shared<bi::Sound>("resources/assets/audio/Soliloquy.mp3");
    //this->smokeTexId = getAssetManager().loadTexture(smokeImage);
    this->drillTexId = getAssetManager().loadTexture(drillPath);

    levelSound->init();
    levelSound->setLoop(true);

    getAudioManager().addSound(levelSound);
    //Loading tmx
    getTileManager().loadTileMap(tilemapPath);
    //createAnimatedSprite();
}

void FirstScene::processInput(float dt) {
    if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_M)) {
        nextScene = "mainmenu";
    }
    playersystem.handleInput(dt);
}

void FirstScene::update(float dt) {

    accDt += dt;
    //getRenderer().setDefaultBlend();

    //if (bi::mouseInput().isDragging) {
    //float x = bi::mouseInput().toOrthoX(getCamera(), getWindow().width);
    //bi::log("Mouse x:",std::to_string(x));

    //float y = bi::mouseInput().toOrthoY(getCamera(), getWindow().height);

    //bi::log("Mouse y:",std::to_string(y));
    //}

    std::vector<bi::TiledObject> &objects = getTileManager().loadTileMap(tilemapPath).getObjects(1);

    playersystem.update(dt, {0, 0}, objects, *this->font);
    //float x = bi::mouseInput().toOrthoX(getCamera(), getWindow().width);
    //bi::log("Mouse x:",std::to_string(x));

    //float y = bi::mouseInput().toOrthoY(getCamera(), getWindow().height);
}

void FirstScene::render(float dt) {
    getRenderer().clear();
    getTileManager().draw(tilemapPath, 0);
    std::vector<bi::TiledObject> &objects = getTileManager().loadTileMap(tilemapPath).getObjects(1);
    ObjectSystem::update(objects, getRenderer());
    getRenderer().drawText("Havested Crystals: ", {0, 15}, *this->font, {1, 1, 0, 1}, 0.1f);
    playersystem.draw(dt);
    getRenderer().endFlushBegin();
    if (showGrid) {
        getTileManager().drawGrid(tilemapPath, {0.4, 0.74, 1, 0.5});
        getShapeRenderer().endFlushBegin();
    }
}

void FirstScene::close() {
    bi::log("closing firstscene");
    levelSound->stopSound();
}


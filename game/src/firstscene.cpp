#include "firstscene.hpp"
#include <cmath>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include "playersystem.hpp"
#include <tmxlite/ObjectGroup.hpp>
#include "objectsystem.hpp"
#include <bismuth/logging.hpp>
#include <memory>
#include <bismuth/animation.hpp>

FirstScene::FirstScene() {}

FirstScene::~FirstScene() {}

void FirstScene::start() {
    levelSound->playSound();
}
void FirstScene::init() {
    this->levelSound = std::make_shared<bi::Sound>("resources/assets/audio/Soliloquy.mp3");
    this->smokeTexId = getAssetManager().loadTexture(smokeImage);
    this->drillTexId = getAssetManager().loadTexture(drillPath);

    levelSound->init();
    levelSound->setLoop(true);

    getAudioManager().addSound(levelSound);
    //Loading tmx
    getTileManager().loadTileMap(tilemapPath);
    //createAnimatedSprite();
}

void FirstScene::createAnimatedSprite() {

    std::vector<int> tileNumbers;

    tileNumbers.push_back(0);
    tileNumbers.push_back(1);
    tileNumbers.push_back(2);
    tileNumbers.push_back(3);

    animatedSprite.addAnimation("right", this->drillTexId, tileNumbers, {16.0f,16.0f}, {1,1,1,1}, 0.05f);

    tileNumbers.clear();

    tileNumbers.push_back(19);
    tileNumbers.push_back(20);
    tileNumbers.push_back(21);
    tileNumbers.push_back(22);

    animatedSprite.addAnimation("left", this->drillTexId, tileNumbers, {16.0f,16.0f}, {1,1,1,1}, 0.05f);

    tileNumbers.clear();

    tileNumbers.push_back(6);
    tileNumbers.push_back(7);
    tileNumbers.push_back(8);
    tileNumbers.push_back(9);

    animatedSprite.addAnimation("up", this->drillTexId, tileNumbers, {16.0f,16.0f}, {1,1,1,1}, 0.05f);

    tileNumbers.clear();

    tileNumbers.push_back(12);
    tileNumbers.push_back(13);
    tileNumbers.push_back(14);
    tileNumbers.push_back(15);

    animatedSprite.addAnimation("down", this->drillTexId, tileNumbers, {16.0f,16.0f}, {1,1,1,1}, 0.05f);

}


void FirstScene::update(float dt) {

    //getRenderer().clear(0.06f,0.04f,0.01f,1);
    getRenderer().clear();
    if (bi::keyInput().isKeyPressed(GLFW_KEY_F)) {
        getWindow().fullscreen(getWindow().width, getWindow().height);
    }

    if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_G)) {
        showGrid = !showGrid;
    }

    //if (bi::mouseInput().isDragging) {
    //float x = bi::mouseInput().toOrthoX(getCamera(), getWindow().width);
    //bi::log("Mouse x:",std::to_string(x));

    //float y = bi::mouseInput().toOrthoY(getCamera(), getWindow().height);

    //bi::log("Mouse y:",std::to_string(y));
    //}

    std::vector<bi::TiledObject>& objects = getTileManager().loadTileMap(tilemapPath).getObjects(0);

    bi::TiledObject& player = getTileManager().loadTileMap(tilemapPath).getObjects(1).at(0);


    getTileManager().draw(tilemapPath, 0);


    //float x = bi::mouseInput().toOrthoX(getCamera(), getWindow().width);
    //bi::log("Mouse x:",std::to_string(x));

    //float y = bi::mouseInput().toOrthoY(getCamera(), getWindow().height);
    //
    //animatedSprite.play("right", dt, {50.0f, 40.0f});
    //animatedSprite.play("left", dt, {30.0f, 40.0f});
    //animatedSprite.play("up", dt, {70.0f, 40.0f});
    //animatedSprite.play("down", dt, {90.0f, 40.0f});

    playersystem.update(dt, player, {0, 0}, smokeTexId);

    //getShapeRenderer().drawRect({100,100}, {100, 50}, {1,1,1,1});
    if (showGrid) {
        getTileManager().drawGrid(tilemapPath, {0.4,0.74,1,0.5});
    }
    getShapeRenderer().endFlushBegin();
    //this->anim->draw(dt, glm::vec2(10.0f,50.0f), 0);
    //getShapeRenderer().drawLine({0,100}, {100,300}, {1,1,0,1});
    ObjectSystem::update(objects, getRenderer());

    getRenderer().endFlushBegin();

    //ObjectSystem::update(object, getRenderer());


    //for (bi::TiledObject o : objects) {
    //getShapeRenderer().drawRect(o.tile.getPosition(), o.tile.getTileSize(), {1,0,1,1}, 0);
    //getRenderer().drawTexture(o.tile.getPosition(), o.tile.getTileSize(), {1,1,1,1}, o.tile.getTextureId(), 0, o.tile.getTexCoords());
    //}



    //getGuiManager().beginDraw();
    //getGuiManager().showFPS();
    //getGuiManager().endDraw();

}

void FirstScene::close() {
    levelSound->stopSound();
}

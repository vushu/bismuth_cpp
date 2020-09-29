#include "firstscene.hpp"
#include <bismuth/assetmanager.hpp>
#include <bismuth/keylistener.hpp>
#include <bismuth/logging.hpp>
#include <bismuth/mouselistener.hpp>
#include <cmath>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include "playersystem.hpp"
#include <tmxlite/ObjectGroup.hpp>
#include "objectsystem.hpp"

FirstScene::FirstScene() {}

FirstScene::~FirstScene() {}

void FirstScene::start() {
    //levelSound->playSound();
}
void FirstScene::init() {
    this->levelSound = std::make_shared<bi::Sound>("resources/assets/audio/Soliloquy.mp3");
    this->smokeTexId = getAssetManager().loadTexture(smokeImage);
    this->drillTexId = getAssetManager().loadTexture(drillPath);


    levelSound->init();
    levelSound->setLoop(true);
    std::vector<int> tileNumbers;
    tileNumbers.push_back(0);
    tileNumbers.push_back(1);
    tileNumbers.push_back(2);
    tileNumbers.push_back(3);
    ////animatedSprite = std::make_unique<bi::Animation>(drillTexId, tileNumbers, {16,16}, {1,1,1,1}, 0.05f);

    getAudioManager().addSound(levelSound);
    //Loading tmx
    getTileManager().loadTileMap(tilemapPath);
}

void FirstScene::update(float dt) {

    getRenderer().clear(0,0,0,1);
    if (bi::keyInput().isKeyPressed(GLFW_KEY_F)) {
        getWindow().fullscreen(getWindow().width, getWindow().height);
    }

    //if (bi::mouseInput().isDragging) {
        //float x = bi::mouseInput().toOrthoX(getCamera(), getWindow().width);
        //bi::log("Mouse x:",std::to_string(x));

        //float y = bi::mouseInput().toOrthoY(getCamera(), getWindow().height);

        //bi::log("Mouse y:",std::to_string(y));
    //}

    std::vector<bi::TiledObject>& objects = getTileManager().loadTileMap(tilemapPath).getObjects(0);

    bi::TiledObject& player = getTileManager().loadTileMap(tilemapPath).getObjects(1).at(0);


    getTileManager().draw(tilemapPath, 0, getRenderer());

    //animatedSprite->draw(getRenderer(), {100, 200}, {16,16}, {1,1,1,1}, 0, dt, 0.05f);
    getRenderer().endFlushBegin();

    //float x = bi::mouseInput().toOrthoX(getCamera(), getWindow().width);
    //bi::log("Mouse x:",std::to_string(x));

    //float y = bi::mouseInput().toOrthoY(getCamera(), getWindow().height);


    playersystem.update(dt, player, getRenderer(), getShapeRenderer(), {0, 0}, smokeTexId);

    getTileManager().drawGrid(tilemapPath, {0.4,0.74,1,0.5});

    ObjectSystem::update(objects, getRenderer());
    //ObjectSystem::update(object, getRenderer());
    //getRenderer().endFlushBegin();


    //for (bi::TiledObject o : objects) {
    //getShapeRenderer().drawRect(o.tile.getPosition(), o.tile.getTileSize(), {1,0,1,1}, 0);
    //getRenderer().drawTexture(o.tile.getPosition(), o.tile.getTileSize(), {1,1,1,1}, o.tile.getTextureId(), 0, o.tile.getTexCoords());
    //}

    //getShapeRenderer().flush();

    getRenderer().endFlushBegin();

    getGuiManager().beginDraw();
    getGuiManager().showFPS();
    getGuiManager().endDraw();

}

void FirstScene::close() {
    levelSound->stopSound();
}

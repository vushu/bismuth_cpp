#include "firstscene.hpp"
#include "../systems/objectsystem.hpp"
#include "../systems/playersystem.hpp"
#include "bismuth/keylistener.hpp"
#include <bismuth/animation.hpp>
#include <bismuth/logging.hpp>
#include <cmath>
#include <memory>
#include <tmxlite/Layer.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/TileLayer.hpp>

FirstScene::FirstScene() { }

FirstScene::~FirstScene()
{

    //nvgDeleteGLES3(vg);
}

void FirstScene::start()
{
    //levelSound->playSound();
}
void FirstScene::init()
{
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

void FirstScene::update(float dt)
{

    if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_LEFT)) {
        nextScene = "mainmenu";
    }
    //getRenderer().clear(0.06f,0.04f,0.01f,1);
    getRenderer().clear();

    if (bi::keyInput().isKeyPressed(GLFW_KEY_F)) {
        getWindow().fullscreen(getWindow().width, getWindow().height);
    }

    if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_G)) {
        showGrid = !showGrid;
    }

    getRenderer().setDefaultBlend();

    //if (bi::mouseInput().isDragging) {
    //float x = bi::mouseInput().toOrthoX(getCamera(), getWindow().width);
    //bi::log("Mouse x:",std::to_string(x));

    //float y = bi::mouseInput().toOrthoY(getCamera(), getWindow().height);

    //bi::log("Mouse y:",std::to_string(y));
    //}

    std::vector<bi::TiledObject>& objects = getTileManager().loadTileMap(tilemapPath).getObjects(1);

    //bi::TiledMap& tiledMap = getTileManager().loadTileMap(tilemapPath);
    //bi::TiledObject& player = tiledMap.getObjects(0).at(0);
    //getTileManager().draw(tilemapPath, 0);
    ObjectSystem::update(objects, getRenderer());
    getRenderer().endFlushBegin();

    playersystem.update(dt, { 0, 0 }, objects, *this->font);

    //getTileManager().draw(tilemapPath, 1);

    //float x = bi::mouseInput().toOrthoX(getCamera(), getWindow().width);
    //bi::log("Mouse x:",std::to_string(x));

    //float y = bi::mouseInput().toOrthoY(getCamera(), getWindow().height);
    //

    //getShapeRenderer().drawLine({0,100}, {100,300}, {1,1,0,1});

    //getRenderer().drawText("Havested Crystals: ", { 0, 15 }, *this->font, { 1, 1, 0, 1 }, 0.1f);
    //getRenderer().endFlushBegin();
    if (showGrid) {
        getTileManager().drawGrid(tilemapPath, { 0.4, 0.74, 1, 0.5 });
        getShapeRenderer().endFlushBegin();
    }

    getGuiManager().beginDraw();
    getGuiManager().showFPS();
    getGuiManager().endDraw();

    //for (bi::TiledObject o : objects) {
    //getShapeRenderer().drawRect(o.tile.getPosition(), o.tile.getTileSize(), {1,0,1,1}, 0);
    //getRenderer().drawTexture(o.tile.getPosition(), o.tile.getTileSize(), {1,1,1,1}, o.tile.getTextureId(), 0, o.tile.getTexCoords());
    //}
}

void FirstScene::close()
{
    bi::log("closing firstscene");
    levelSound->stopSound();
}

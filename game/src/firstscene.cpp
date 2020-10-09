#include "firstscene.hpp"
#include "bismuth/keylistener.hpp"
#include "objectsystem.hpp"
#include "playersystem.hpp"
#include <bismuth/animation.hpp>
#include <bismuth/logging.hpp>
#include <cmath>
#include <memory>
#include <tmxlite/Layer.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/TileLayer.hpp>
#define NANOVG_GLES3_IMPLEMENTATION
#include <nanovg/nanovg_gl.h>
#include <nanovg/nanovg_gl_utils.h>

FirstScene::FirstScene() { }

FirstScene::~FirstScene()
{

    nvgDeleteGLES3(vg);
}

void FirstScene::start()
{
    levelSound->playSound();
}
void FirstScene::init()
{
    vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

    if (vg == nullptr) {
        throw std::runtime_error("Failed to create nanovg instance");
    }

    bi::log("Successfully created nanovg instance");

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

    playersystem.update(dt, player, { 0, 0 }, smokeTexId);

    //getShapeRenderer().drawRect({100,100}, {100, 50}, {1,1,1,1});
    //if (showGrid) {
    //}
    //this->anim->draw(dt, glm::vec2(10.0f,50.0f), 0);
    //getShapeRenderer().drawLine({0,100}, {100,300}, {1,1,0,1});
    ObjectSystem::update(objects, getRenderer());

    getRenderer().endFlushBegin();

    //getTileManager().drawGrid(tilemapPath, {0.4,0.74,1,0.5});
    //getShapeRenderer().endFlushBegin();

    //for (bi::TiledObject o : objects) {
    //getShapeRenderer().drawRect(o.tile.getPosition(), o.tile.getTileSize(), {1,0,1,1}, 0);
    //getRenderer().drawTexture(o.tile.getPosition(), o.tile.getTileSize(), {1,1,1,1}, o.tile.getTextureId(), 0, o.tile.getTexCoords());
    //}

    float pxRatio = getWindow().maxWidth / getWindow().maxHeight;
    nvgBeginFrame(vg, getWindow().maxWidth, getWindow().maxHeight, pxRatio);
    //nvgSave(vg);

    nvgBeginPath(vg);
    nvgCircle(vg, 100, 100, 40);

    nvgRect(vg, 100, 100, 120, 30);
    nvgFillColor(vg, nvgRGBA(255, 192, 0, 255));
    nvgFill(vg);

    //nvgRestore(vg);
    nvgEndFrame(vg);

    //getGuiManager().beginDraw();
    //getGuiManager().showFPS();
    //getGuiManager().endDraw();
}

void FirstScene::close()
{
    bi::log("closing firstscene");
    levelSound->stopSound();
}

#include "firstscene.hpp"

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
}


void FirstScene::update(float dt) {
    getShapeRenderer().drawPolygon({100,100}, 30.0, 12, {0,0,1,1}, 0);
    getShapeRenderer().flush();

    getGuiManager().beginDraw();
    getGuiManager().showFPS();
    getGuiManager().endDraw();

}

void FirstScene::close() {
    levelSound->stopSound();
}

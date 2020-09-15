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

    getGuiManager().beginDraw();
    getGuiManager().showFPS();
    getGuiManager().endDraw();

}

void FirstScene::close() {
    levelSound->stopSound();
}

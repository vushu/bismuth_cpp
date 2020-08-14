#include "game.hpp"
#include "bismuth/application.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/texture.hpp"
#include "components.hpp"
#include <algorithm>
#include <entt/entt.hpp>
#include <string>
#include "entitybuilder.hpp"


MyGame::~MyGame() {}

void MyGame::update(float dt) {
    if (bi::keyInput().isKeyPressed(GLFW_KEY_ESCAPE)) {
        bi::log("Escape Pushed");
        getWindow().close();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_S)) {
        bi::log("STOP audioManager");
        this->getAudioManager().stop();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_UP)) {
        bi::log("Start sound");
        s4->playSound();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_DOWN)) {
        bi::log("Stopping sound");
        s4->stopSound();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_SPACE)) {
        this->s2->stopSound();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_R)) {
        bi::log("rewind sound");
        s4->rewindSound();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_1)) {
        this->getAudioManager().stop();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_3)) {
        this->s2->playSound();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_D)) {
        this->getAudioManager().start();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_RIGHT)) {
        s2->incrementVolume(0.1f);
        bi::log("volume is " + std::to_string(s2->volume));
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_LEFT)) {
        s2->decrementVolume(0.1f);
        bi::log("volume is " + std::to_string(s2->volume));

    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_P) && s1->isPause) {
        s1->isPause = false;
    }

    renderSystem.update(this->getRenderer(), dt , this->registry);

}

void MyGame::init() {
    s1 = std::make_shared<bi::Sound>("resources/assets/audio/test.wav");
    s2 = std::make_shared<bi::Sound>("resources/assets/audio/music2.mp3");
    s3 = std::make_shared<bi::Sound>("resources/assets/audio/music3.mp3");
    s4 = std::make_shared<bi::Sound>("resources/assets/audio/music4.mp3");

    s1->init();
    s2->init();
    s3->init();
    s4->init();
    s4->setLoop(true);
    //s1->loop = true;
    //s4->loop = true;
    //s2->loop = true;
    // must be initialized since not all games want to have sound
    getAudioManager().init();
    getAudioManager().addSound(s1);
    getAudioManager().addSound(s2);
    getAudioManager().addSound(s4);
    getAudioManager().addSound(s3);
    //sound2.playLoop("resources/assets/audio/test.wav");
    std::unique_ptr<EntityBuilder> entitybuilder = std::make_unique<EntityBuilder>();
    entitybuilder->at(100.0f, 100.0f )
        .size(400, 400)
        .vel(3, 2)
        .sprite("resources/assets/images/awesomeface.png")
        .buildPlayer(this->getRenderer(),this->registry);

}

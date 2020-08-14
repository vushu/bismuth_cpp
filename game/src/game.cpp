#include "game.hpp"
#include "bismuth/application.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/texture.hpp"
#include "components.hpp"
#include <algorithm>
#include <entt/entt.hpp>
#include "entitybuilder.hpp"


MyGame::~MyGame() {}
bool once = false;
bool once2 = false;

void MyGame::update(float dt) {
    //bi::log(std::to_string(1/dt));
    if (bi::keyInput().isKeyPressed(GLFW_KEY_ESCAPE)) {
        bi::log("Escape Pushed");
        window->close();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_S)) {
        //bi::log("Enter Pushed");
        bi::log("STOP audioManager");
        this->audioManager->stop();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_UP)) {
        //bi::log("Enter Pushed");
        bi::log("Start sound");
        s4->isPause = false;
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_DOWN)) {
        //bi::log("Enter Pushed");
        bi::log("Start sound");
        s4->isPause = true;
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_SPACE)) {
        //bi::log("Enter Pushed");
        bi::log("End sound");
        this->s2->isPause = true;
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_R)) {
        //bi::log("Enter Pushed");
        bi::log("replay sound");
        this->s4->replay = true;
        this->s4->isDone = false;
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_1)) {
        //bi::log("Enter Pushed");
        this->audioManager->stop();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_3)) {
        //bi::log("Enter Pushed");
        this->s2->isPause = false;
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_D)) {
        //bi::log("Enter Pushed");
        this->audioManager->start();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_RIGHT)) {
        //bi::log("Enter Pushed");
        s2->volume += 0.1;
        s2->volume = std::min(s2->volume, 1.0f);
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_LEFT)) {
        //bi::log("Enter Pushed");
        s2->volume -= 0.1f;
        s2->volume = std::max(s2->volume, 0.0f);

    }
    renderSystem.update(this->getRenderer(), dt , this->registry);

}

void MyGame::init() {
    std::shared_ptr<bi::Sound> s1 = std::make_shared<bi::Sound>("resources/assets/audio/music.mp3");
    s2 = std::make_shared<bi::Sound>("resources/assets/audio/music2.mp3");

    s3 = std::make_shared<bi::Sound>("resources/assets/audio/music3.mp3");
    s4 = std::make_shared<bi::Sound>("resources/assets/audio/music4.mp3");
    s1->init();
    s2->init();
    s3->init();
    s4->init();
    s4->loop = true;
    s2->loop = true;
    audioManager->init();
    audioManager->addSound(s1);
    audioManager->addSound(s2);
    audioManager->addSound(s4);
    audioManager->addSound(s3);
    //sound2.playLoop("resources/assets/audio/test.wav");
    std::unique_ptr<EntityBuilder> entitybuilder = std::make_unique<EntityBuilder>();
    entitybuilder->at(100.0f, 100.0f )
        .size(400, 400)
        .vel(3, 2)
        .sprite("resources/assets/images/awesomeface.png")
        .buildPlayer(this->getRenderer(),this->registry);

}

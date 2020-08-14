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
#include <box2d/box2d.h>

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

    renderSystem.update(this->getRenderer(), dt, boxBody , this->registry);
    //update world
    world.Step(1.0/30.0, 8,3);

}

void MyGame::init() {


    //box2d
    groundBodyDef.position.Set(0.0f * P2M, 590.0f * P2M);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    groundBodyDef.type = b2_staticBody;
    b2FixtureDef fixtureDef2;
    b2PolygonShape shape2;
    shape2.SetAsBox(500*P2M,10*P2M);
    fixtureDef2.shape = &shape2;
    fixtureDef2.density = 1.0;
    groundBody->CreateFixture(&fixtureDef2);

    //groundBody->CreateFixture(&groundBox, 0.0f);

    boxBodyDef.position.Set(100 * P2M, 100 * P2M);
    boxBodyDef.type = b2_dynamicBody;
    boxBody = world.CreateBody(&boxBodyDef);
    b2FixtureDef fixtureDef;
    b2PolygonShape shape;
    shape.SetAsBox(100*P2M,100*P2M);
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0;
    boxBody->CreateFixture(&fixtureDef);





    s1 = std::make_shared<bi::Sound>("resources/assets/audio/test.wav");
    s2 = std::make_shared<bi::Sound>("resources/assets/audio/music2.mp3");
    s3 = std::make_shared<bi::Sound>("resources/assets/audio/music3.mp3");
    //s4 = std::make_shared<bi::Sound>("resources/assets/audio/tower.mp3");
    s4 = std::make_shared<bi::Sound>("resources/assets/audio/music4.mp3");

    s1->init();
    s2->init();
    s3->init();
    s4->init();
    s4->setLoop(true);
    // must be initialized since not all games want to have sound
    getAudioManager().init();
    getAudioManager().addSound(s1);
    getAudioManager().addSound(s2);
    getAudioManager().addSound(s4);
    getAudioManager().addSound(s3);
    getAudioManager().setMaxVolume(3.0f);
    //sound2.playLoop("resources/assets/audio/test.wav");
    std::unique_ptr<EntityBuilder> entitybuilder = std::make_unique<EntityBuilder>();
    entitybuilder->at(100.0f, 100.0f )
        .size(200, 200)
        .vel(3, 2)
        .setColor(glm::vec4(1,1,1,1))
        .sprite("resources/assets/images/awesomeface.png")
        .buildPlayer(this->getRenderer(),this->registry);


    // box
    entitybuilder->at(0.0f, 590.0f )
        .size(1000, 10.0f)
        .vel(0, 0)
        .setColor(glm::vec4(1,0,1,1))
        .buildPlayer(this->getRenderer(),this->registry);


}

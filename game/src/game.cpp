#include "game.hpp"
#include "bismuth/application.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/renderino.hpp"
#include "bismuth/sprite.hpp"
#include "bismuth/spriterenderer.hpp"
#include "bismuth/texture.hpp"
#include "components.hpp"
#include <algorithm>
#include <entt/entt.hpp>
#include <memory>
#include <string>
#include "entitybuilder.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include <box2d/box2d.h>
#include <bismuth/physicsmanager.hpp>
#include <bismuth/assetmanager.hpp>
#include <imgui/imgui.h>
using namespace bi;

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


    //renderSystem.update(this->getRenderer(), dt, world, this->registry);
    //update world
    //world.Step(1.0f/60.0f, 6, 2);
    //world.Step(1.0f/60.0f, 6, 2);
    //float timeStep = 1.0f/60.0f;      //the length of time passed to simulate (seconds)
    //int velocityIterations = 6;   //how strongly to correct velocity
    //int positionIterations = 2;   //how strongly to correct position
    //bi::log("FPS: " + std::to_string(1.0f/dt));
    // since we are using variable time put dt
    //world.Step(dt, velocityIterations, positionIterations);
    this->getRenderer().resetStats();
    this->getRenderer().beginBatch();
    //for (int i = 0; i < 100; ++i) {

    glm::vec4 color{1,0,1,1};
    position.y = sin(ticks/50);
    position.x += 10 * dt;

    this->getRenderer().drawQuad({0.0f,0.0f}, {10.0f,10.0f}, color);
    this->getRenderer().drawQuad(position, {30.0f,30.0f}, {1,1,1,1});
    //}

    //this->getRenderer().draw(*this->spriterenderer);
    this->getRenderer().endBatch();
    this->getRenderer().flush();

    //log("QuadCounts: "  + std::to_string(this->getRenderer().getRenderStats().quadCount));
    //log("draw Calls: "  + std::to_string(this->getRenderer().getRenderStats().drawCount));
    //this->getRenderer().


    getGuiManager().beginDraw();
    getGuiManager().showFPS();
    ImGui::Begin("Render stats");
    ImGui::Text("Quads: %s", std::to_string(this->getRenderer().getRenderStats().quadCount).c_str());
    ImGui::Text("DrawCount: %s", std::to_string(this->getRenderer().getRenderStats().drawCount).c_str());
    ImGui::End();

    getGuiManager().endDraw();
    ticks++;

}

void MyGame::init() {

    //getRenderer().init();
    getGuiManager().init();
    //this->renderino = std::make_unique<bi::Renderino>(this->getCamera());
    //this->getRenderer().beginBatch();
    std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>();
    this->spriterenderer = std::make_unique<bi::SpriteRenderer>(std::move(sprite));

    this->spriterenderer->setColor(glm::vec4(1,0,0,1));
    this->spriterenderer->setPosition(glm::vec2(0,0));
    this->spriterenderer->setScale(glm::vec2(32,32));


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
    //std::unique_ptr<EntityBuilder> entitybuilder = std::make_unique<EntityBuilder>();
    //std::unique_ptr<EntityBuilder> entitybuilder2 = std::make_unique<EntityBuilder>();

    //entitybuilder->at(100, 100)
    //.size(100, 100)
    //.vel(3, 2)
    //.setColor(glm::vec4(1,1,1,1))
    //.sprite("resources/assets/images/tennis.png")
    //.buildEnemy(this->getRenderer(), this->world, this->registry, true);
    /*
       EntityBuilder en;

       en.at(0, 590)
       .size(1000, 10)
       .vel(3, 2)
       .setColor(glm::vec4(1,0,0,1))
    //.sprite("resources/assets/images/tennis.png")
    .buildEnemy(this->getRenderer(), this->world, this->registry, true, true);

    en.at(0, 0)
    .size(10, 600)
    .vel(3, 2)
    .setColor(glm::vec4(0,1,0,1))
    //.sprite("resources/assets/images/tennis.png")
    .buildEnemy(this->getRenderer(), this->world, this->registry, true, true);

    en.at(790, 0)
    .size(10, 600)
    .vel(3, 2)
    .setColor(glm::vec4(0,0,1,1))
    //.sprite("resources/assets/images/tennis.png")
    .buildEnemy(this->getRenderer(), this->world, this->registry, true, true);


    for (int i = 0; i < 220; i++) {
    EntityBuilder entitybuilder;
    entitybuilder.at(60 + (i), 10 + i)
    .size(25,25)
    .vel(3, 2)
    //.setColor(glm::vec4(i/10.0f,i/100.0f,sin(i*20),1))
    //.setColor(glm::vec4(i/10.0f,i/100.0f,sin(i*20),1))
    .sprite("resources/assets/images/tennis.png", this->getAssetManager())
    .buildEnemy(this->getRenderer(), this->world, this->registry, false, false);
    }

*/


    //entitybuilder->at(120, 200)
    //.size(50, 50)
    ////.vel(3, 2)
    //.setColor(glm::vec4(1,0,1,1))
    //.sprite("resources/assets/images/ball2.png")
    //.buildEnemy(this->getRenderer(), this->world, this->registry, false);

    //boxBody = entitybuilder->at(100, 100)
    //.size(100, 100)
    //.vel(3, 2)
    ////.setColor(glm::vec4(1,1,1,1))
    //.sprite("resources/assets/images/tennis.png")
    //.buildEnemy(this->getRenderer(), this->world, this->registry, true);


}

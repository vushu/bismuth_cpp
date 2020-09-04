#include "game.hpp"
#include "bismuth/logging.hpp"
#include "components.hpp"
#include <bismuth/bismuth.hpp>
#include <entt/entt.hpp>
#include <memory>
#include <string>
#include "entitybuilder.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include <box2d/box2d.h>
#include <imgui/imgui.h>
#include "shapebuilder.hpp"
#include "playerball.hpp"
using namespace bi;

MyGame::~MyGame() {}


void MyGame::update(float dt) {

    if (bi::keyInput().isKeyPressed(GLFW_KEY_ESCAPE)) {
        bi::log("Escape Pushed");
        getWindow().close();
    }
    /*
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

*/

    //update world
    //world.Step(1.0f/60.0f, 6, 2);
    //world.Step(1.0f/60.0f, 6, 2);
    //float timeStep = 1.0f/60.0f;      //the length of time passed to simulate (seconds)
    int velocityIterations = 4;   //how strongly to correct velocity
    int positionIterations = 2;   //how strongly to correct position
    //bi::log("FPS: " + std::to_string(1.0f/dt));
    // since we are using variable time put dt
    renderSystem->update(*this->shaperenderer, this->getRenderer() ,dt, world, registry);
    //this->getRenderer().drawTexture({400, 280}, {100.0f,100.0f}, {1,1,1,1}, textureId, glm::pi<float>() * mAngle);
    world.Step(dt, velocityIterations, positionIterations);
    //playerball->draw(getRenderer());
    //
    //
    //
    mAngle += dt;
    drawStuff2(dt);
    //drawStuff(dt);

}

void MyGame::drawStuff(float dt) {
    this->shaperenderer->drawPolygon({400, 200}, 50.0f, 4, {0,1,0,1}, M_PI * mAngle , true);
    this->shaperenderer->drawPolygon({400, 240}, 50.0f, 5, {1,1,0,1}, M_PI * mAngle , true);
    //this->shaperenderer->drawPolygon({200, 200}, 50.0f, 3, {0,1,0,1}, 0.0f , true);

    this->shaperenderer->drawLine({10,200}, {500,200}, {1,0,0,1});
    //this->shaperenderer->drawLine({10,300}, {500,300}, color);
    this->shaperenderer->drawPolygon({300, 300}, 50.0f, 24, {0,0,1,1}, M_PI * mAngle, true);
    this->shaperenderer->flush();
}

void MyGame::drawStuff2(float dt) {
    //this->getRenderer().resetStats();
    //this->getRenderer().beginBatch();
    //for (int i = 0; i < 100; ++i) {

    glm::vec4 colorSmiley{1,1,1,1};

    //this->getRenderer().drawTexture({camX, camY}, {100.0f,100.0f}, color, textureId, glm::pi<float>() * -mAngle);
    //this->getRenderer().drawTexture({214, 280}, {100.0f,100.0f}, colorSmiley, textureId, glm::pi<float>() * mAngle);

    //this->getRenderer().drawTexture({400, 280}, {100.0f,100.0f}, colorSmiley, textureId, glm::pi<float>() * mAngle);
    //this->getRenderer().drawQuad({200, 300}, {30.0f,30.0f}, {1,1,1,1});
    //getRenderer().drawTexture({400,200}, playerball->mSize, {1,1,1,1}, playerball->mTextureId, M_PI * mAngle);
    //this->getRenderer().drawText(text, {0, 125}, *this->font, this->textColor, 0.4f);

    //this->getRenderer().endBatch();
    //this->getRenderer().flush();

    getGuiManager().beginDraw();
    ImGui::Begin("Render stats");
    ImGui::Text("Quads: %s", std::to_string(this->getRenderer().getRenderStats().quadCount).c_str());
    ImGui::Text("DrawCount: %s", std::to_string(this->getRenderer().getRenderStats().drawCount).c_str());
    ImGui::Text("Average %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("%.1f FPS)", ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Begin("Camera Pos");
    ImGui::SliderFloat("CamX:", &camX, -1000, 1000);
    ImGui::SliderFloat("CamY:", &camY, -1000, 1000);
    ImGui::InputText("Text", text.data(), text.size());
    ImGui::End();

    ImGui::Begin("Color");
    ImGui::ColorPicker4("Color", &color[0]);
    ImGui::End();

    ImGui::Begin("Text Color");
    ImGui::ColorPicker4("TextColor", &textColor[0]);
    ImGui::End();
    getGuiManager().endDraw();

}

void MyGame::init() {

    position = {0,0};
    size = {100,100};
    //getCamera().setPosition(glm::vec2 pos)
    //getCamera().viewMatrix = glm::translate(getCamera().viewMatrix, glm::vec3(100,0,0));
    shaperenderer = std::make_unique<bi::ShapeRenderer>(getCamera());
    shaperenderer->init();
    renderSystem = std::make_unique<RenderSystem>();
    getGuiManager().init();

    std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>();
    font = std::make_unique<Font>(getAssetManager());
    font->loadFnt("resources/assets/fonts/manjaru.fnt");
    textureId = getAssetManager().loadTexture("resources/assets/images/awesomeface.png");
    bi::log("TextureId: ", std::to_string(textureId));
    shapeBuilder = std::make_unique<ShapeBuilder>();

    playerball = std::make_unique<PlayerBall>(textureId);

    shapeBuilder->
        setPosition(140.0f, 100.0f)
        .setRadius(30.0f)
        .setUserData(&playerball)
        //.setTexture(textureId)
        .buildBall(this->world, registry);

    shapeBuilder->
        setPosition(140.0f, 0.0f)
        .setRadius(20.0f)
        //.isStatic(true)
        .buildBall(this->world, registry);

    for (int i = 0; i < 3000; i++) {
        shapeBuilder->
            setPosition(i * 10, 10)
            .setRadius(10.0f)
            //.isStatic(true)
            .buildBall(this->world, registry);
    }


    shapeBuilder->setPosition(100.0f, 700.0f)
        .setRadius(500.0f)
        //.setTexture(textureId)
        .isStatic(true)
        .buildBall(this->world, registry);

}

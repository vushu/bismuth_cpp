#include "game.hpp"
#include "bismuth/editors/asseteditor.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/mouselistener.hpp"
#include "./components/components.hpp"
#include <bismuth/bismuth.hpp>
#include <cstdio>
#include <entt/entt.hpp>
#include <memory>
#include <string>
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "./builders/entitybuilder.hpp"
#include "./scenes/firstscene.hpp"
#include <box2d/box2d.h>
#include <imgui/imgui.h>
#include "glm/gtx/string_cast.hpp"
#include "./scenes/main_menu_scene.hpp"
#include "./builders/shapebuilder.hpp"
#include "./systems/playerball.hpp"
#include "./factories/factories.hpp"
#include "./systems/rectrendersystem.hpp"
#include "./scenes/mainmenu.hpp"
#include <map>
using namespace bi;

MyGame::~MyGame() {}


void MyGame::update(float dt) {

    if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_ESCAPE)) {
        bi::log("Escape Pushed");
        getWindow().close();
    }
    //if (bi::mouseInput().isDragging){
    //float x = bi::mouseInput().toOrthoX(getCamera(), getWindow().width);
    //bi::log("Mouse x:",std::to_string(x));
    //float y = bi::mouseInput().toOrthoY(getCamera(), getWindow().height);
    //bi::log("Mouse y:",std::to_string(y));
    //}

    if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_1)) {
        //bi::log("Scene changed");
        this->getSceneManager().setScene("mainmenu");
    }
    else if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_2)) {
        //bi::log("Scene changed");
        this->getSceneManager().setScene("firstscene");
    }
    else if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_3)) {
        //bi::log("Scene changed");
        this->getSceneManager().setScene("asseteditor");
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

    int velocityIterations = 4;   //how strongly to correct velocity
    int positionIterations = 2;   //how strongly to correct position
    //renderSystem->update(this->getShapeRenderer(), this->getRenderer(), dt, world, registry);

    //RectRenderSystem::update(registry, *this->shaperenderer, mAngle * M_PI);
    //this->getRenderer().drawTexture({400, 280}, {100.0f,100.0f}, {1,1,1,1}, textureId, glm::pi<float>() * mAngle);
    //world.Step(dt, velocityIterations, positionIterations);
    //playerball->draw(getRenderer());
    //
    //mAngle += dt;
    //drawStuff2(dt);
    //drawStuff(dt);
    //getGuiManager().beginDraw();
    //getGuiManager().showFPS();
    //getGuiManager().endDraw();
    //for (auto& s : scenes) {
    //s.second->update(dt);
    //((Scene)s.second);
    //}
}

void MyGame::drawStuff(float dt) {
    //getMainFramebuffer().bind();
    this->getShapeRenderer().drawPolygon({400, 200}, 50.0f, 4, {0,1,0,1}, M_PI * mAngle , true);
    this->getShapeRenderer().drawPolygon({400, 240}, 50.0f, 5, {1,1,0,1}, M_PI * mAngle , true);
    //this->shaperenderer->drawPolygon({200, 200}, 50.0f, 3, {0,1,0,1}, 0.0f , true);

    //this->shaperenderer->drawLine({10,200}, {500,500}, {1,0,1,1});
    //this->shaperenderer->drawLine({10,200}, {500,500}, {1,1,0,1}, M_PI * mAngle);
    //this->shaperenderer->drawLine({10,300}, {500,300}, color);
    //this->shaperenderer->drawPolygon({300, 300}, 50.0f, 24, {0,0,1,1}, M_PI * mAngle, true);
    this->getShapeRenderer().flush();
    //getMainFramebuffer().unbind();

    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
    //glClear(GL_COLOR_BUFFER_BIT);
    //this->getRenderer().drawTexture({100,100}, {400, 350}, {1,1,1,1}, getMainFramebuffer().textureId, 0);
    //this->shaperenderer->flush();
}

void MyGame::drawStuff2(float dt) {
    this->getRenderer().resetStats();
    //this->getRenderer().beginBatch();
    //for (int i = 0; i < 100; ++i) {

    glm::vec4 colorSmiley{1,1,1,1};

    //this->getRenderer().drawTexture({camX, camY}, {100.0f,100.0f}, color, textureId, glm::pi<float>() * -mAngle);
    this->getRenderer().drawTexture({214, 280}, {100.0f,100.0f}, colorSmiley, textureId, glm::pi<float>() * mAngle);

    this->getRenderer().drawTexture({400, 280}, {100.0f,100.0f}, colorSmiley, textureId, glm::pi<float>() * mAngle);
    //this->getRenderer().drawQuad({200, 300}, {30.0f,30.0f}, {1,1,1,1});
    //getRenderer().drawTexture({400,200}, playerball->mSize, {1,1,1,1}, playerball->mTextureId, M_PI * mAngle);
    //this->getRenderer().drawText(text, {0, 125}, *this->font, this->textColor, 0.4f);
    getRenderer().endFlushBegin();
    //this->getRenderer().endBatch();
    //this->getRenderer().flush();

    getGuiManager().beginDraw();
    ImGui::Begin("Render stats");
    ImGui::Text("Quads: %s", std::to_string(this->getRenderer().getRenderStats().quadCount).c_str());
    ImGui::Text("DrawCount: %s", std::to_string(this->getRenderer().getRenderStats().drawCount).c_str());
    ImGui::Text("Average %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
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

    //getGuiManager().init();
    // Scene registration
    std::unique_ptr<MainMenuScene> mainMenu = std::make_unique<MainMenuScene>();
    this->getSceneManager().addScene("mainmenu", std::move(mainMenu));
    //
    //std::unique_ptr<MainMenuSceneB> mainMenu = std::make_unique<MainMenuSceneB>();
    //this->getSceneManager().addScene("mainmenu", std::move(mainMenu));

    //std::unique_ptr<MainMenuSceneB> mainMenu = std::make_unique<MainMenuSceneB>();
    //this->getSceneManager().addScene("mainmenu", std::move(mainMenu));

    std::unique_ptr<FirstScene> firstScene = std::make_unique<FirstScene>();
    this->getSceneManager().addScene("firstscene", std::move(firstScene));

    //std::unique_ptr<MainMenuSceneB> mainMenu = std::make_unique<MainMenuSceneB>();
    //this->getSceneManager().addScene("mainmenu", std::move(mainMenu));
    std::unique_ptr<AssetEditor> asseteditor = std::make_unique<AssetEditor>();
    this->getSceneManager().addScene("asseteditor", std::move(asseteditor));



    //renderSystem = std::make_unique<RenderSystem>();
    getAudioManager().init();
    getAudioManager().start();

    //std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>();
    //font = std::make_unique<Font>(getAssetManager());
    //font->loadFnt("resources/assets/fonts/manjaru.fnt");
    //textureId = getAssetManager().loadTexture("resources/assets/images/awesomeface.png");
    //bi::log("TextureId: ", std::to_string(textureId));
    //shapeBuilder = std::make_unique<ShapeBuilder>();

    //playerball = std::make_unique<PlayerBall>(textureId);

    /*
       shapeBuilder->
       setPosition(140.0f, 100.0f)
       .setRadius(30.0f)
    //.setTexture(textureId)
    .setUserData(&getAssetManager().getTexture("resources/assets/images/awesomeface.png"))
    .buildBall(this->world, registry);

    shapeBuilder->
    setPosition(140.0f, 0.0f)
    .setRadius(20.0f)
    .setUserData(&getAssetManager().getTexture("resources/assets/images/awesomeface.png"))
    //.isStatic(true)
    .buildBall(this->world, registry);

    for (int i = 0; i < 2000; i++) {
    shapeBuilder->
    setPosition(i * 10, 10)
    .setRadius(10.0f)
    .setUserData(&getAssetManager().getTexture("resources/assets/images/awesomeface.png"))
    //.isStatic(true)
    .buildBall(this->world, registry);
    }
    */
    //Factories::createRect(registry, {100, 100}, {100, 50});

    //shapeBuilder->setPosition(100.0f, 700.0f)
    //.setRadius(500.0f)
    ////.setTexture(textureId)
    //.isStatic(true)
    //.buildBall(this->world, registry);

}

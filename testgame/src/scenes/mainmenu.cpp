#include "mainmenu.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/sound.hpp"
#include <bismuth/logging.hpp>
#include <string>
#include <imgui/imgui.h>

MainMenuScene::MainMenuScene() {}

MainMenuScene::~MainMenuScene() {}

void MainMenuScene::start() {
    //mainMenuMusic->playSound();
}


void MainMenuScene::init() {
    getGuiManager().init();

    this->mainMenuMusic = std::make_shared<bi::Sound>("resources/assets/audio/mainmenu.wav");
    this->tower = std::make_shared<bi::Sound>("resources/assets/audio/tower.mp3");
    tower->init();
    tower->setLoop(true);
    mainMenuMusic->init();
    mainMenuMusic->setLoop(true);
    getAudioManager().addSound(mainMenuMusic);
    getAudioManager().addSound(tower);


    textureId = getAssetManager().loadTexture("resources/assets/images/awesomeface.png");
}

void MainMenuScene::drawMenu() {

    getGuiManager().beginDraw();

    ImGui::SetNextWindowSize(ImVec2(menuWidth, menuHeight));
    bool open = true;

    ImGui::SetNextWindowPos(
            ImVec2(getWindow().width / 2.0f - menuWidth / 2, getWindow().height / 2.0f - menuHeight / 2));
    if (ImGui::Begin(" ", &open,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize)) {
        if (ImGui::Button("Start", ImVec2(buttonWidth, buttonHeight))) {
            //this->mainMenuMusic->stopSound();
            this->nextScene = "firstscene";
        }

        if (ImGui::Button("Fullscreen", ImVec2(buttonWidth, buttonHeight))) {
            getWindow().fullscreen(getWindow().maxWidth, getWindow().maxHeight);
        }
        if (ImGui::Button("Exit", ImVec2(buttonWidth, buttonHeight))) {
            bi::log("exit clicked ");
            getWindow().close();
        }
        ImGui::End();


    }

    getGuiManager().endDraw();


}

void MainMenuScene::setStyle() {

    ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(.4f, .4f, .55f, .8f);
    ImGui::GetStyle().ItemInnerSpacing = ImVec2(0.f, 4.f);
    ImGui::GetStyle().ItemSpacing = ImVec2(0.f, 4.f);
    ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);

    ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor::HSV(0 / 7.0f, 0.6f, 0.6f);
    ImGui::GetStyle().ItemInnerSpacing = ImVec2(4.f, 4.f);
    ImGui::GetStyle().ItemSpacing = ImVec2(4.f, 4.f);


}

void MainMenuScene::update(float dt) {

    //accTime += dt;
}

void MainMenuScene::processInput(float dt) {
    if (bi::keyInput().isKeyPressed(GLFW_KEY_P)) {
        bi::log("Start sound");
        mainMenuMusic->playSound();
    } else if (bi::keyInput().isKeyPressed(GLFW_KEY_T)) {
        bi::log("Start sound");
        tower->playSound();
    } else if (bi::keyInput().isKeyPressed(GLFW_KEY_W)) {
        getWindow().windowed(getWindow().width, getWindow().height);
    }
}

void MainMenuScene::render(float dt) {
    getRenderer().clear();
    setStyle();
    drawMenu();
    accTime += dt;
}

void MainMenuScene::close() {
    bi::log("closing mainMenuMusic");
    //tower->stopSound();
    mainMenuMusic->stopSound();
    //mainMenuMusic->pauseSound();
}

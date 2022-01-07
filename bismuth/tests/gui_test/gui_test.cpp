#include "gui_test.hpp"
#include "bismuth/color.hpp"
#include "bismuth/gui/gui_label.hpp"
#include "bismuth/gui/gui_window.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/mouselistener.hpp"
#include <catch2/catch.hpp>
#include "bismuth/keyboard.hpp"
#include <iostream>
#include <memory>
#include <string>

GuiTest::~GuiTest() {
}

void GuiTest::setupGuiEvents() {

    bi::gui::GuiButtonCallback callback = [&](bi::gui::GuiButton& button) {
        if (button.isPressed){
            button.setSize({300, 50});
            button.setText("NUOC MAM");
            button.positionBottomCenterTo(button.getParent().position, button.getParent().size);
            getAudioManager().playSound(explosionSoundFile);
        }
        else {
            bi::log("IS RELEASED");
        }
    };

    startBtn->onLeftClick(callback);

    startBtn->onMouseOver([&](bi::gui::GuiButton& button){
        button.setTextColor(bi::color::SOFT_YELLOW);
        button.outlineColor = bi::color::SOFT_YELLOW;
        getAudioManager().playSound(bismuthSoundFile);
        button.backgroundColor = bi::color::SOFT_MAGENTA;
    });

    counter.onCount([&](int count){

        fpsLabel->setText("Countdown: " + std::to_string(count));
        fpsLabel->positionTopCenterTo({0,0}, getWindow().size());

        if (count <= 3 && count >= 1){
            getAudioManager().getSound(plingSoundFile).playSound(true);
        }

        if (count == 0){
            fpsLabel->setText("Shutting down!");
            fpsLabel->positionTopCenterTo({0,0}, getWindow().size());
            getAudioManager().getSound(explosionSoundFile).playSound(true);
        }
        if (count == -1){
            getWindow().close();
        }

    });

    window->onMouseOver([&](bi::gui::GuiWindow& window){
        if (window.isMouseOver) {
            window.setOutlineColor(bi::color::SOFT_GREEN);
        }
        else {
            window.setOutlineColor(bi::color::SOFT_YELLOW);
        }
    });

}
void GuiTest::init() {

    testSceneOne = std::make_unique<TestSceneOne>();
    guiTexture = std::make_shared<bi::gui::GuiTexture>("resources/assets/textures/bismuth/bismuth_text.png");
    guiTexture->init();
    guiTexture->setScale(0.5f);
    guiTexture->setOffset({10, -10});
    guiTexture->positionBottomLeftTo({0,0}, this->getWindow().size());
    //testSceneTwo = std::make_unique<TestSceneTwo>();
    //getSceneManager().addScene("testSceneOne", std::move(testSceneOne));
    //getSceneManager().addScene("testSceneOne", std::move(testSceneTwo));

    window = std::make_unique<bi::gui::GuiWindow>();
    fpsLabel = std::make_shared<bi::gui::GuiLabel>();
    startBtn = std::make_shared<bi::gui::GuiButton>();

    bi::mouseInput().hideCursor();

    getAudioManager().init();
    getAudioManager().start();

    bismuthSoundFile = getAudioManager().addSound("resources/assets/audio/bismuth.wav");
    plingSoundFile = getAudioManager().addSound("resources/assets/audio/pling.wav");
    explosionSoundFile = getAudioManager().addSound("resources/assets/audio/explosion.wav");

    window->setSize(getWindow().size() * 0.5f);

    fpsLabel->setFont(&getAssetManager().getDefaultFont());
    fpsLabel->setText("Countdown: " + std::to_string(counter.getCount()));
    fpsLabel->setColor(bi::color::WHITE);
    fpsLabel->setOffset({0, 12});
    fpsLabel->positionTopCenterTo({0,0}, getWindow().size());

    startBtn->setSize({260,50});
    startBtn->setTextColor(bi::color::WHITE);
    startBtn->setFont(&getAssetManager().getDefaultFont());
    window->add(startBtn, bi::gui::CENTER);

    window->setBackgroundColor(bi::color::fromRGB(0, 5, 253, 0.4f));
    //window->addBackgroundTexture("resources/assets/textures/bismuth/bismuth_text.png");

    startBtn->setText("Play Sound");
    window->positionCenterTo({0,0}, getWindow().size());
    //window->positionCenterTo({0,0}, getWindow().size());

    //testSceneOne->init();

    //window->addScene(testSceneOne.get());

    setupGuiEvents();

}

void GuiTest::update(float dt) {
    counter.updateDecrement(dt);
}

void GuiTest::processInput(float dt) {
    window->processInput();

    if (bi::keyInput().isKeyPressed(bi::Key::ESCAPE)){
        getWindow().close();
    }
}

void GuiTest::render(float dt) {

    getRenderer().clear();

    guiTexture->draw();

    fpsLabel->draw();

    window->draw();

    getCursor().draw();

    //getShapeRenderer().drawRect(fpsLabel->position, fpsLabel->size, bi::color::CORNFLOWER_BLUE);
    getShapeRenderer().drawRect(window->position, window->size, bi::color::SOFT_GREEN);

    getShapeRenderer().endFlushBegin();

    getRenderer().endFlushBegin();

}

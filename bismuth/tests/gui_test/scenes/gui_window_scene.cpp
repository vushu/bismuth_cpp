#include "gui_window_scene.hpp"
#include "bismuth/gui/gui_button.hpp"

GuiWindowScene::GuiWindowScene() {}

GuiWindowScene::~GuiWindowScene() {}

void GuiWindowScene::setupGuiEvents() {

    counter.onCount([&](int count){
            fpsLabel->setText("Countdown: " + std::to_string(count));
            fpsLabel->positionTopCenterTo({0,0}, getWindow().size());

            if (count <= 3 && count >= 1){
            getAudioManager().getSound(tickSoundFile).playSound(true);
            }

            if (count == 0){
            fpsLabel->setText("Shutting down!");
            fpsLabel->positionTopCenterTo({0,0}, getWindow().size());
            getAudioManager().getSound(explosionSoundFile).playSound(true);
            }
            if (count == -1){
            getWindow().close();
            }});
    startBtn->onMouseOver([&](bi::gui::GuiButton& button){
            startBtn->outlineColor = bi::color::SOFT_GREEN;
            startBtn->backgroundColor = bi::color::fromRGB(100, 100, 0, 0.5f);
            getAudioManager().getSound("resources/assets/audio/button_hover.mp3").playSound();
            });
    startBtn->onLeftMousePressed([&](bi::gui::GuiButton&){
            getAudioManager().getSound("resources/assets/audio/explosion.wav").playSound();
            });
    startBtn->onLeftMouseReleased([&](bi::gui::GuiButton&){
            //getAudioManager().playSound("resources/assets/audio/pling.wav");
            });
    window->onMouseOver([&](bi::gui::GuiWindow& win){
            if (win.isMouseOver)
                win.setBackgroundColor({1,0.5f, 0.4f,0.6f});
            else
            win.setBackgroundColor({0,0,0,1});
            });

}

void GuiWindowScene::init() {

    tickSoundFile = getAudioManager().getSound("resources/assets/audio/tick.mp3").filepath;
    plingSoundFile = getAudioManager().getSound("resources/assets/audio/pling.wav").filepath;
    explosionSoundFile = getAudioManager().getSound("resources/assets/audio/explosion.wav").filepath;

    window = std::make_unique<bi::gui::GuiWindow>();
    startBtn = std::make_shared<bi::gui::GuiButton>();
    fpsLabel = std::make_shared<bi::gui::GuiLabel>();
    fpsLabel->setOffset({0, 10});

    startBtn->setSize({260,50});
    startBtn->setTextColor(bi::color::WHITE);
    startBtn->setText("Play explosion");

    window->setBackgroundColor(bi::color::BLACK);
    window->setSize({500, 300});
    window->add(startBtn, bi::gui::CENTER);

    startBtn->setText("Play Sound");

    startBtn->positionCenterTo({0,0}, getWindow().size());
    window->positionCenterTo({0,0}, getWindow().size());

    setupGuiEvents();
}

void GuiWindowScene::start() {}

void GuiWindowScene::processInput(float dt) {
    window->processInput();
}

void GuiWindowScene::update(float dt) {
    counter.updateDecrement(dt);
}

void GuiWindowScene::render(float dt) {

    getRenderer().clear();

    fpsLabel->draw();
    window->draw();

    getCursor().draw();
    getRenderer().endFlushBegin();

}

void GuiWindowScene::close() {}


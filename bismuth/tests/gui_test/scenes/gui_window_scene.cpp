#include "gui_window_scene.hpp"

GuiWindowScene::GuiWindowScene() {}

GuiWindowScene::~GuiWindowScene() {}

void GuiWindowScene::setupGuiEvents() {

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
        }});

}

void GuiWindowScene::init() {

    //bismuthSoundFile = getAudioManager().getSound("resources/assets/audio/bismuth.wav").filepath;
    plingSoundFile = getAudioManager().getSound("resources/assets/audio/pling.wav").filepath;
    explosionSoundFile = getAudioManager().getSound("resources/assets/audio/explosion.wav").filepath;

    //window = std::make_unique<bi::gui::GuiWindow>();
    //startBtn = std::make_shared<bi::gui::GuiButton>();
    fpsLabel = std::make_shared<bi::gui::GuiLabel>(getAssetManager().getDefaultFont());

    //startBtn->setSize({260,50});
    //startBtn->setTextColor(bi::color::WHITE);
    //startBtn->setFont(&getAssetManager().getDefaultFont());

    //window->add(startBtn, bi::gui::CENTER);

    //window->setBackgroundColor(bi::color::fromRGB(0, 5, 253, 0.4f));
    //startBtn->setSize({260,50});
    //startBtn->setTextColor(bi::color::WHITE);
    //startBtn->setFont(&getAssetManager().getDefaultFont());

    //window->add(startBtn, bi::gui::CENTER);

    //window->setBackgroundColor(bi::color::fromRGB(0, 5, 253, 0.4f));

    //startBtn->setText("Play Sound");

    //window->add(guiTexture, bi::gui::BOTTOM_LEFT);
    //window->positionCenterTo({0,0}, getWindow().size());

    setupGuiEvents();
}

void GuiWindowScene::start() {}

void GuiWindowScene::processInput(float dt) {}

void GuiWindowScene::update(float dt) {
    counter.updateDecrement(dt);
}

void GuiWindowScene::render(float dt) {

    fpsLabel->draw();

    //window->draw();

    //getCursor().draw();

    //getShapeRenderer().drawRect(window->position, window->size, bi::color::SOFT_GREEN);

    //getShapeRenderer().endFlushBegin();


}

void GuiWindowScene::close() {}


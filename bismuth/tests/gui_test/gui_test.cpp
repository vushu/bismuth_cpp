#include "gui_test.hpp"
#include "bismuth/color.hpp"
#include "bismuth/gui/guilabel.hpp"
#include "bismuth/gui/guiwindow.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/mouselistener.hpp"
#include <catch2/catch.hpp>
#include <string>

void GuiTest::init() {
    bi::mouseInput().hideCursor();
    getAudioManager().init();
    getAudioManager().start();

    bismuthSoundFile = getAudioManager().addSound("resources/assets/audio/bismuth.wav");
    plingSoundFile = getAudioManager().addSound("resources/assets/audio/pling.wav");

    SECTION("Render gui window") {
        window.setSize({300, 300});
        fpsLabel.setFont(&getAssetManager().getDefaultFont());
        fpsLabel.setColor(bi::color::WHITE);
        fpsLabel.setText("Countdown: " + std::to_string(counter.getCount()));
        fpsLabel.setOffset({0, 12});
        fpsLabel.positionTopCenterTo({0,0}, getWindow().size());

        startBtn.setSize({260,50});
        startBtn.setTextColor(bi::color::WHITE);
        startBtn.setFont(&getAssetManager().getDefaultFont());
        window.add(&startBtn, bi::gui::CENTER);
        window.setBackgroundColor(bi::color::fromRGB(0, 5, 253, 0.5));
        startBtn.setText("Play Sound");
        window.positionCenterTo({0,0}, getWindow().size());
    }

}

void GuiTest::update(float dt) {

    if (window.isPositionWithinRect(bi::mouseInput().getPosition())) {
        window.setOutlineColor(bi::color::SOFT_GREEN);
    }
    else {
        window.setOutlineColor(bi::color::SOFT_RED);
    }

    if (startBtn.isPositionWithinRect(bi::mouseInput().getPosition())){
        startBtn.setTextColor(bi::color::SOFT_YELLOW);
        startBtn.outlineColor = bi::color::SOFT_YELLOW;
        startBtn.backgroundColor = bi::color::SOFT_RED;
        getCursor().setMouseOver(true);
    }
    else{
        startBtn.setTextColor(bi::color::WHITE);
        startBtn.outlineColor = bi::color::SOFT_MAGENTA;
        startBtn.backgroundColor = bi::color::CORNFLOWER_BLUE;
        getCursor().setMouseOver(false);
    }

    if (startBtn.mouseClicked()) {
        getAudioManager().getSound(bismuthSoundFile).playSound(true);
    }

    if (startBtn.mouseReleased()){
    }

    if (counter.countDown(dt)) {
        fpsLabel.setText("Countdown: " + std::to_string(counter.getCount()));
        fpsLabel.positionTopCenterTo({0,0}, getWindow().size());

        if (counter.getCount() <= 3){
            getAudioManager().getSound(plingSoundFile).playSound(true);
        }
        if (counter.getCount() == 0){
            fpsLabel.setText("Shutting down!");
            fpsLabel.positionTopCenterTo({0,0}, getWindow().size());
        }
        if (counter.getCount() == -1){
            getWindow().close();
        }
    }

}

void GuiTest::processInput(float dt) {

    if (bi::keyInput().isKeyPressed(GLFW_KEY_ESCAPE)){
        getWindow().close();
    }
}

void GuiTest::render(float dt) {
    getRenderer().clear();

    fpsLabel.draw();
    getShapeRenderer().drawRect(fpsLabel.position, fpsLabel.size, bi::color::CORNFLOWER_BLUE);
    getShapeRenderer().endFlushBegin();

    window.draw();

    getCursor().draw();

    getRenderer().endFlushBegin();

}

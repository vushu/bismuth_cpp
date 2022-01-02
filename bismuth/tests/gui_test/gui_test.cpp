#include "gui_test.hpp"
#include "bismuth/color.hpp"
#include "bismuth/gui/guilabel.hpp"
#include "bismuth/gui/guiwindow.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/mouselistener.hpp"
#include <catch2/catch.hpp>
#include <string>

void GuiTest::init() {
    SECTION("Render gui window") {
        window.setSize({300, 300});

        fpsLabel.setFont(&getAssetManager().getDefaultFont());
        fpsLabel.setColor(bi::color::WHITE);
        fpsLabel.setText("Countdown: " + std::to_string(counter));
        fpsLabel.setOffset({0, 12});
        fpsLabel.positionTopCenterTo({0,0}, getWindow().size());

        startBtn.setSize({200,40});
        startBtn.setTextColor(bi::color::WHITE);
        startBtn.setFont(&getAssetManager().getDefaultFont());
        //startBtn.positionCenterTo({0,0}, getWindow().size());
        window.add(&startBtn, bi::gui::CENTER);
        window.setBackgroundColor(bi::color::fromRGB(0, 5, 253, 0.5));
        startBtn.setText("START");
        window.positionCenterTo({0,0}, getWindow().size());
        handId = getAssetManager().loadTexture(cursorHandPath);
        pointerId = getAssetManager().loadTexture(cursorPointerPath);
    }

}

void GuiTest::update(float dt) {
    accDt += dt;

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

    if (accDt > 1) {
        counter--;
        fpsLabel.setText("Countdown: " + std::to_string(counter));
        fpsLabel.positionTopCenterTo({0,0}, getWindow().size());
        accDt = 0;
    }

    if (counter <= 0){
        fpsLabel.setText("Shutting down!");
        fpsLabel.positionTopCenterTo({0,0}, getWindow().size());
    }

    //fpsLabel.positionTopCenterTo({0,0}, getWindow().size());
    if (counter <= -1){
        //getWindow().close();
    }

}

void GuiTest::processInput(float dt) {
    window.processDragging();

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

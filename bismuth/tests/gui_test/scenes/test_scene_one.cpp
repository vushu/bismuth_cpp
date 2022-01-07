#include "test_scene_one.hpp"
#include "bismuth/gui/gui_label.hpp"

TestSceneOne::TestSceneOne() {}

TestSceneOne::~TestSceneOne() {}

void TestSceneOne::init() {
    titleLabel = std::make_unique<bi::gui::GuiLabel>();
    titleLabel->setFont(&getAssetManager().getDefaultFont());
    titleLabel->setText("TEST SCENE ONE!!!");
    titleLabel->setColor(bi::color::WHITE);
    titleLabel->positionCenterTo({0,0}, getWindow().size());
}

void TestSceneOne::start() {}

void TestSceneOne::processInput(float dt) {}

void TestSceneOne::update(float dt) {}

void TestSceneOne::render(float dt) {
    bi::log("RENDERING", "TESTSCENEONE!!!");
    titleLabel->draw();
}

void TestSceneOne::close() {}


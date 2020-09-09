#include "mainmenu.hpp"
#include "bismuth/logging.hpp"
#include <string>

MainMenuScene::MainMenuScene() {}

MainMenuScene::~MainMenuScene() {}

void MainMenuScene::update(float dt) {

    bi::log("Rendering main menu", std::to_string(dt)) ;
}

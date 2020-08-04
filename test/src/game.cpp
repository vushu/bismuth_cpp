#include "game.hpp"
#include "bismuth/application.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/texture.hpp"


MyGame::~MyGame() {}

void MyGame::update(float dt) {
    //bi::log(std::to_string(1/dt));
    if (bi::keyInput().isKeyPressed(GLFW_KEY_ESCAPE)) {
        bi::log("Escape Pushed");
        window->close();
    }
}

void MyGame::init() {
    bi::log("hej");
    bi::log("hej");
    bi::log("hej");
    bi::log("hej");
    bi::Texture texture;
    texture.init("resources/mipmaps.png");
}

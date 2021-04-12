#include "game.hpp"
#include "bismuth/keylistener.hpp"

Game::~Game() {}

void Game::init() {

}

void Game::processInput(float dt) {
    if (bi::keyInput().isKeyPressed(GLFW_KEY_ESCAPE))  {
        this->getWindow().close();
    }
}

void Game::update(float dt) {

}

void Game::render(float dt) {

}

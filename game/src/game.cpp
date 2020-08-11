#include "game.hpp"
#include "bismuth/application.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/texture.hpp"
#include "components.hpp"
#include <entt/entt.hpp>
#include "entitybuilder.hpp"


MyGame::~MyGame() {}

void MyGame::update(float dt) {
    //bi::log(std::to_string(1/dt));
    if (bi::keyInput().isKeyPressed(GLFW_KEY_ESCAPE)) {
        bi::log("Escape Pushed");
        window->close();
    }
    renderSystem.update(this->getRenderer(), dt , this->registry);
}

void MyGame::init() {
    std::unique_ptr<EntityBuilder> entitybuilder = std::make_unique<EntityBuilder>();
    entitybuilder->at(100.0f, 100.0f )
        .size(400, 400)
        .vel(3, 2)
        .sprite("resources/assets/images/awesomeface.png")
        .buildPlayer(this->getRenderer(),this->registry);

}

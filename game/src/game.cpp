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

    std::shared_ptr<bi::Texture> texture = std::make_shared<bi::Texture>("resources/assets/images/awesomeface.png");
    texture->init();
    std::unique_ptr<bi::Sprite> sprite = std::make_unique<bi::Sprite>(texture);

    std::unique_ptr<bi::SpriteRenderer> spriterenderer = std::make_unique<bi::SpriteRenderer>(std::move(sprite));
    spriterenderer->setPosition(glm::vec2(100,0));
    spriterenderer->setScale(glm::vec2(100,49));
    renderer->addSprite(std::move(spriterenderer));

}

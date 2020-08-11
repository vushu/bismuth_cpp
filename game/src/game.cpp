#include "game.hpp"
#include "bismuth/application.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/texture.hpp"
#include "components.hpp"
#include <entt/entt.hpp>


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

    auto entity = registry.create();
    registry.emplace<Movement>(entity, 10,10);
    std::shared_ptr<bi::Texture> texture = std::make_shared<bi::Texture>("resources/assets/images/awesomeface.png");
    texture->init();

    std::unique_ptr<bi::Sprite> sprite = std::make_unique<bi::Sprite>(texture);
    std::shared_ptr<bi::SpriteRenderer> spriterenderer = std::make_shared<bi::SpriteRenderer>(std::move(sprite));

    spriterenderer->setPosition(glm::vec2(100,0));
    spriterenderer->setScale(glm::vec2(100,100));
    bi::RenId rid = renderer->addSprite(std::move(spriterenderer));
    bi::log("batch id " + std::to_string(rid.batchId));
    bi::log("sprite id " + std::to_string(rid.spriteId));
    registry.emplace<Player>(entity, rid.batchId, rid.spriteId);



}

#include "entitybuilder.hpp"
#include "components.hpp"
#include <entt/entt.hpp>
#include <glm/glm.hpp>

EntityBuilder:: EntityBuilder() {}
EntityBuilder::~EntityBuilder() {}

EntityBuilder& EntityBuilder::at(float x, float y) {
    this->position = glm::vec2(x, y);
    return *this;
}

EntityBuilder& EntityBuilder::vel(float x, float y) {
    this->velocity = glm::vec2(x, y);
    return *this;
}


EntityBuilder& EntityBuilder::size(float x, float y) {
    this->scale = glm::vec2(x, y);
    return *this;
}

EntityBuilder& EntityBuilder::color(glm::vec4 color) {
    std::unique_ptr<bi::Sprite> sprite = std::make_unique<bi::Sprite>();
    spr = std::make_shared<bi::SpriteRenderer>(std::move(sprite));
    spr->setColor(color);

    return *this;
}

EntityBuilder& EntityBuilder::sprite(std::string filepath) {
    std::shared_ptr<bi::Texture> texture = std::make_shared<bi::Texture>(filepath);

    std::unique_ptr<bi::Sprite> sprite = std::make_unique<bi::Sprite>(std::move(texture));
    spr= std::make_shared<bi::SpriteRenderer>(std::move(sprite));

    return *this;
}

void EntityBuilder::buildPlayer(bi::Renderer& renderer, entt::registry& registry) {
    spr->initTexture();
    spr->setScale(this->scale);
    spr->setPosition(this->position);
    this->rid = renderer.addSprite(std::move(spr));
    auto entity = registry.create();

    registry.emplace<Player>(entity, rid.batchId, rid.spriteId);
    registry.emplace<Movement>(entity, velocity.x, velocity.y);

}




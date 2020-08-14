#include "entitybuilder.hpp"
#include "components.hpp"
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <bismuth/logging.hpp>
#include <memory>

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

EntityBuilder& EntityBuilder::setColor(glm::vec4 color) {
    this->color = color;
    return *this;
}

EntityBuilder& EntityBuilder::sprite(std::string filepath) {
    std::shared_ptr<bi::Texture> texture = std::make_shared<bi::Texture>(filepath);
    this->msprite = std::make_unique<bi::Sprite>(std::move(texture));
    spr = std::make_shared<bi::SpriteRenderer>(std::move(msprite));
    return *this;
}

void EntityBuilder::buildPlayer(bi::Renderer& renderer, entt::registry& registry) {

    if (spr == nullptr) {
        bi::log("null spr");
        spr = std::make_shared<bi::SpriteRenderer>(std::make_unique<bi::Sprite>());
    }
    spr->color = color;
    spr->initTexture();
    spr->setScale(this->scale);
    spr->setPosition(this->position);

    this->rid = renderer.addSprite(std::move(spr));

    auto entity = registry.create();

    registry.emplace<Player>(entity, rid.batchId, rid.spriteId);
    registry.emplace<Movement>(entity, velocity.x, velocity.y);
    reset();

}

void EntityBuilder::reset() {
    //spr.reset();
    this->rid = {};
    position = glm::vec2(0,0);
    scale = glm::vec2(32,32);
    color = glm::vec4(1,1,1,1);
    velocity = glm::vec2(1,1);

}





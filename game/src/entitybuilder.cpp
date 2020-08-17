#include "entitybuilder.hpp"
#include <box2d/box2d.h>
#include "components.hpp"
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <bismuth/logging.hpp>
#include <memory>
#include <bismuth/physicsmanager.hpp>

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
void EntityBuilder::buildEnemy(bi::Renderer& renderer, b2World& world, entt::registry& registry, bool isStatic, bool isBox) {

    bi::log("create entity");
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

    //registry.emplace<Player>(entity, rid.batchId, rid.spriteId);
    registry.emplace<Movement>(entity, velocity.x, velocity.y);
    //reset();
    buildBox(world, renderer, isStatic, isBox);

}

void EntityBuilder::buildBox(b2World& world, bi::Renderer& renderer, bool isStatic, bool isBox) {
    b2BodyDef bodyDef;
    bodyDef.userData = &renderer.getSprite(this->rid.batchId, this->rid.spriteId);
    //coordinate system i at the center
    //bodyDef.position.Set(this->position.x * bi::P2M, this->position.y * bi::P2M);
    float x = (this->position.x + this->scale.x * 0.5f) * bi::P2M;
    float y = (this->position.y + this->scale.y * 0.5f) * bi::P2M;
    //float x = this->position.x  * bi::P2M;
    //float y = this->position.y  * bi::P2M;
    bi::log("x: " + std::to_string(x));
    bi::log("y: " + std::to_string(y));
    bodyDef.position.Set(x, y);

    if (isStatic) {
        bodyDef.type = b2_staticBody;
    }
    else {
        bodyDef.type = b2_dynamicBody;
    }

    b2Body* body = world.CreateBody(&bodyDef);

    b2FixtureDef fixtureDef2;
    if (isBox) {
        b2PolygonShape dynamicBox;
        //shape2.SetAsBox(10,10);
        //dynamicBox.SetAsBox(bi::P2M * this->scale.x/2.0f, bi::P2M * this->scale.y/2.0f);
        dynamicBox.SetAsBox(bi::P2M * this->scale.x/2.0f, bi::P2M * this->scale.y/2.0f);
        //this->scale.y * 0.5f * bi::P2M);

        fixtureDef2.shape = &dynamicBox;
        fixtureDef2.density = 1.0f;
        fixtureDef2.friction = 0.3f;
        fixtureDef2.restitution = 0.4f;

        body->CreateFixture(&fixtureDef2);

    }
    else {
        b2CircleShape dynamicBox;
        dynamicBox.m_radius = bi::P2M * this->scale.x/2.0f;

        //b2PolygonShape dynamicBox;
        //shape2.SetAsBox(10,10);
        //dynamicBox.SetAsBox(this->scale.x * 0.5f * bi::P2M,
        //this->scale.y * 0.5f * bi::P2M);

        fixtureDef2.shape = &dynamicBox;
        fixtureDef2.density = 100.0f;
        fixtureDef2.friction = 0.3f;
        fixtureDef2.restitution = 0.4f;

        body->CreateFixture(&fixtureDef2);
    }
    //reset();
}

void EntityBuilder::buildPlayer(bi::Renderer& renderer, entt::registry& registry) {

    bi::log("create entity");
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





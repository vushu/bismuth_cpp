#include "shapebuilder.hpp"
#include "bismuth/physicsmanager.hpp"
#include <entt/entt.hpp>
#include "components.hpp"

ShapeBuilder::ShapeBuilder() {}
ShapeBuilder::~ShapeBuilder() {}


ShapeBuilder& ShapeBuilder::setRadius(float radius) {
    this->radius = radius;
    return *this;
}

ShapeBuilder& ShapeBuilder::setPosition(float x, float y) {
    this->position = glm::vec2(x, y);
    return *this;
}

ShapeBuilder& ShapeBuilder::isStatic(bool enable) {
    this->staticObject = enable;
    return *this;
}

ShapeBuilder& ShapeBuilder::setTexture(int texId) {
    this->textureId = texId;
    return *this;
}


void ShapeBuilder::buildBall(b2World& world, entt::registry& registry) {

    float x = (this->position.x + radius * 0.5f) * bi::P2M;
    float y = (this->position.y + radius * 0.5f) * bi::P2M;


    Ball ball {radius, textureId};
    auto e = registry.create();
    registry.emplace<Ball>(e, ball);


    b2BodyDef bodyDef;
    bodyDef.position.Set(x, y);
    b2MassData massData;
    massData.I = 4;
    massData.mass = 10;
    massData.center = b2Vec2_zero;

    if (!staticObject)
        bodyDef.type = b2_dynamicBody;

    if (staticObject)
        bodyDef.type = b2_staticBody;


    b2Body* body = world.CreateBody(&bodyDef);

    body->SetUserData(&e);
    body->SetMassData(&massData);

    b2FixtureDef fixtureDef;
    b2CircleShape circleShape;
    circleShape.m_radius = radius * bi::P2M;
    circleShape.m_p.Set(0.0f, 0.0f);
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.7f;

    body->CreateFixture(&fixtureDef);
    //fixtureDef.userData = {radius, 0,0,0};
    reset();
}

void ShapeBuilder::reset() {
    radius = 0.0f;
    position ={0,0};
    color = {1,1,1,1};
    velocity = {1,1};
    size = {32,32};
}

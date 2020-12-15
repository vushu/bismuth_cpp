#include "drill.hpp"
#include <bismuth/animatedsprite.hpp>
#include <bismuth/iomanager.hpp>

Drill::Drill() { }

Drill::~Drill() { }

void Drill::init()
{
    this->drillTexId = bi::ioManager().assetmanager->loadTexture(drillPath);
    createAnimatedSprite();
}

void Drill::playAnimationRight(float dt, glm::vec2 position)
{
    animatedSprite.play("right", dt, position);
}

void Drill::playAnimationLeft(float dt, glm::vec2 position)
{
    animatedSprite.play("left", dt, position);
}

void Drill::playAnimationUp(float dt, glm::vec2 position)
{
    animatedSprite.play("up", dt, position);
}

void Drill::playAnimationDown(float dt, glm::vec2 position)
{
    animatedSprite.play("down", dt, position);
}

void Drill::playAnimation(float dt, std::string animationName,  glm::vec2 position)
{
    animatedSprite.play(animationName, dt, position);
}

void Drill::createAnimatedSprite()
{

    std::vector<int> tileNumbers;

    tileNumbers.push_back(0);
    tileNumbers.push_back(1);
    tileNumbers.push_back(2);
    tileNumbers.push_back(3);

    animatedSprite.addAnimation("right", this->drillTexId, tileNumbers, { 16.0f, 16.0f }, { 1, 1, 1, 1 }, 0.05f);

    tileNumbers.clear();

    tileNumbers.push_back(19);
    tileNumbers.push_back(20);
    tileNumbers.push_back(21);
    tileNumbers.push_back(22);

    animatedSprite.addAnimation("left", this->drillTexId, tileNumbers, { 16.0f, 16.0f }, { 1, 1, 1, 1 }, 0.05f);

    tileNumbers.clear();

    tileNumbers.push_back(6);
    tileNumbers.push_back(7);
    tileNumbers.push_back(8);
    tileNumbers.push_back(9);

    animatedSprite.addAnimation("up", this->drillTexId, tileNumbers, { 16.0f, 16.0f }, { 1, 1, 1, 1 }, 0.05f);

    tileNumbers.clear();

    tileNumbers.push_back(12);
    tileNumbers.push_back(13);
    tileNumbers.push_back(14);
    tileNumbers.push_back(15);

    animatedSprite.addAnimation("down", this->drillTexId, tileNumbers, { 16.0f, 16.0f }, { 1, 1, 1, 1 }, 0.05f);
}

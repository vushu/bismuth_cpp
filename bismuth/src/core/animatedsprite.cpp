#include <bismuth/animatedsprite.hpp>
using namespace bi;

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::~AnimatedSprite() {}

void AnimatedSprite::addAnimation(std::string name, int texId, std::vector<int> tileNumbers, glm::vec2 size, glm::vec4 color, float frameTime) {
    Animation anim(texId, tileNumbers, size, color, frameTime);
    animations.emplace(name, std::move(anim));
}

void AnimatedSprite::play(std::string name, float dt, glm::vec2 position, float angle) {
    if (animations.count(name) > 0) {
        animations.at(name).draw(dt, position, angle);
    }
}

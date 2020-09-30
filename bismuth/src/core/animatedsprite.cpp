#include <bismuth/animatedsprite.hpp>
#include <bismuth/logging.hpp>
using namespace bi;

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::~AnimatedSprite() {}

void AnimatedSprite::addAnimation(std::string name, int texId, std::vector<int> tileNumbers, glm::vec2 size, glm::vec4 color, float frameTime) {
    Animation anim(name,texId, tileNumbers, size, color, frameTime);
    animations.emplace(name, std::move(anim));
}

void AnimatedSprite::addAnimation(Animation animation) {

    animations.emplace(animation.name, std::move(animation));
}
void AnimatedSprite::play(std::string name, float dt, glm::vec2 position, float angle) {
    if (animations.count(name) > 0) {
        animations.at(name).draw(dt, position, angle);
    }
    else {
        bi::log("Animation \"" + name + "\" Not found");
    }
}

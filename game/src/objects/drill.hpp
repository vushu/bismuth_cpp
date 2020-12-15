#pragma once
#include <bismuth/animatedsprite.hpp>
class Drill {
public:
    // constructors, asssignment, destructor
    Drill();
    ~Drill();

    void init();
    void play();
    void playAnimationRight(float dt, glm::vec2 position);
    void playAnimationLeft(float dt, glm::vec2 position);
    void playAnimationUp(float dt, glm::vec2 position);
    void playAnimationDown(float dt, glm::vec2 position);
    void playAnimation(float dt, std::string animationName, glm::vec2 position);
private:
    int drillTexId;
    std::string drillPath = "resources/assets/images/drill.png";
    bi::AnimatedSprite animatedSprite;
    void createAnimatedSprite();
};

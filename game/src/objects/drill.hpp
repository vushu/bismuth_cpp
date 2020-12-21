#pragma once
#include <bismuth/animatedsprite.hpp>

struct Node {
public:
    glm::vec2 position;
    struct Node* next;
};

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
    void draw(float dt);
    Node* drillNode;
    Node* current;

private:
    int drillTexId;
    std::string drillPath = "resources/assets/images/drill.png";
    bi::AnimatedSprite animatedSprite;
    void createAnimatedSprite();
};

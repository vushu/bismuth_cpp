#pragma once

#include <bismuth/animatedsprite.hpp>
#include <queue>

struct Node {
public:
    int number;
    glm::vec2 position;
    glm::vec2 direction = {1, 0};


    struct Node *parent;
    struct Node *next;
    glm::vec2 lastTile;
    glm::vec2 nextDirection = {1, 0};
    bool isHead;
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

    void draw(float dt, glm::vec2 direction, float speed);

    glm::vec2 lastTile{16, 16};
    float accDt = 0.0f;
    Node *drillNode;
    Node *appendPointer;

    glm::vec2 getCurrentTile(glm::vec2 newPos, glm::vec2 dir);

    glm::vec2 lastCurrentTile(glm::vec2 newPos, glm::vec2 dir);

    void setLastTile();

    void prepend(glm::vec2 tile, glm::vec2 direction);

    void append();

    int tailLength = 24;
    int lastTailLength = tailLength;

    bool snapToGrid(Node* cart);

    void changeDirection(Node* cart);


private:
    glm::vec2 right{1, 0};
    glm::vec2 left{-1, 0};
    glm::vec2 up{0, -1};
    glm::vec2 down{0, 1};

    int drillTexId;
    int cartTexId;
    std::string drillPath = "resources/assets/images/drill.png";
    std::string cartPath = "resources/assets/images/cart.png";
    bi::AnimatedSprite animatedSprite;

    void createAnimatedSprite();
};

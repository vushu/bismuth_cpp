#pragma once

#include "bismuth/keylistener.hpp"
#include "bismuth/particle.hpp"
#include "bismuth/particleemitter.hpp"
#include "bismuth/renderer.hpp"
#include "bismuth/shaperenderer.hpp"
#include "bismuth/tiledmap.hpp"
#include "glm/gtc/constants.hpp"
#include <queue>
#include "../objects/drill.hpp"
#include "../particles/dust_trail.hpp"

class PlayerSystem {

public:
    PlayerSystem();

    ~PlayerSystem();

    void draw(float dt);
    void handleInput(float dt);
    void update(float dt, glm::vec2 mouse, std::vector<bi::TiledObject> &objects, bi::Font &font);

private:
    std::vector<glm::vec2> tail;
    glm::vec2 zero{0, 0};
    float accDt;
    Drill drill;
    std::string currentAnimation;
    int crystals = 0;
    float DRAW_RATE = 1.0f/30.0f;

    glm::vec2 newPos{0, 0};
    glm::vec2 direction{0, 0};
    glm::vec2 currentDir{1, 0};
    glm::vec2 newDirection{0, 0};
    glm::vec2 lastTile{0, 0};
    glm::vec2 currentTile{0, 0};
    std::queue<glm::vec2> directionQueue;
    glm::vec2 right{1, 0};
    glm::vec2 left{-1, 0};
    glm::vec2 up{0, -1};
    glm::vec2 down{0, 1};
    bool keyDown = false;
    float speed = 1.0f;
    float maxSpeed = 7.0f;
    float maxSpeedVariableStep = 479.94;
    float newSpeed = 0.0f;
    bool moving = false;
    bool win = false;
    glm::vec2 particleOffset{0, 0};
    std::unique_ptr<bi::Font> font;

    glm::vec2 getCurrentTile(glm::vec2 dir);

    glm::vec2 setNextTile(glm::vec2 point);

    glm::vec2 getNextTile();

    void drawRight(bi::ShapeRenderer &shaperenderer);

    void drawLeft(bi::ShapeRenderer &shaperenderer);

    void drawUp(bi::ShapeRenderer &shaperenderer);

    void drawDown(bi::ShapeRenderer &shaperenderer);

    void drawDirection(bi::ShapeRenderer &shaperenderer);

    bool xAxisMoving();

    bool yAxisMoving();

    void showDirection();

    void inputHandleDirection(glm::vec2 direction, int key);

    DustTrail dustTrail;

    void handleCollision(std::vector<bi::TiledObject> &objects, bi::Font &font);

    void snapToGrid();

    void updateSpeed();

};


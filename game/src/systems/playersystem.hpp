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
        void update(float dt, bi::TiledObject player, glm::vec2 mouse);
    private:
        glm::vec2 zero {0,0};
        float accDt;
        Drill drill;
        std::string currentAnimation;

        glm::vec2 newPos{0,0};
        glm::vec2 direction{0,0};
        glm::vec2 currentDir{0,0};
        glm::vec2 newDirection {0,0};
        glm::vec2 lastTile {0,0};
        glm::vec2 currentTile {0,0};
        std::queue<glm::vec2> directionQueue;
        glm::vec2 right{1,0};
        glm::vec2 left{-1,0};
        glm::vec2 up{0,-1};
        glm::vec2 down{0,1};
        bool keyDown = false;
        float speed = 90;
        bool moving = false;
        glm::vec2 particleOffset {0,0};

        glm::vec2 getCurrentTile(glm::vec2 dir);
        glm::vec2 setNextTile(glm::vec2 point);
        glm::vec2 getNextTile();

        void drawRight(bi::ShapeRenderer& shaperenderer);
        void drawLeft(bi::ShapeRenderer& shaperenderer);
        void drawUp(bi::ShapeRenderer& shaperenderer);
        void drawDown(bi::ShapeRenderer& shaperenderer);
        void drawDirection(bi::ShapeRenderer& shaperenderer);
        bool xAxisMoving();
        bool yAxisMoving();
        void showDirection();
        DustTrail dustTrail;


};
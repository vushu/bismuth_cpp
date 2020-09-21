#pragma once
#include "bismuth/keylistener.hpp"
#include "bismuth/renderer.hpp"
#include "bismuth/shaperenderer.hpp"
#include "bismuth/tiledmap.hpp"
#include "glm/gtc/constants.hpp"
#include <queue>
class PlayerSystem{

    public:
        PlayerSystem();
        ~PlayerSystem();
        void update(float dt, bi::TiledObject player, bi::Renderer& renderer, bi::ShapeRenderer& shaperenderer, glm::vec2 mouse);
    private:
        glm::vec2 newPos{0,0};
        glm::vec2 direction{0,0};
        glm::vec2 currentDir{0,0};
        glm::vec2 nextTile {0,0};
        glm::vec2 currentTile {0,0};
        std::queue<glm::vec2> directionQueue;
        glm::vec2 right{1,0};
        glm::vec2 left{-1,0};
        glm::vec2 up{0,-1};
        glm::vec2 down{0,1};
        float speed = 100;
        bool hit = false;
        glm::vec2 getCurrentTile();
        glm::vec2 setNextTile();

        void drawRight();
        void drawLeft();
        void drawUp();
        void drawDown();



};

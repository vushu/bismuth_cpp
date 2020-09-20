#pragma once
#include "bismuth/keylistener.hpp"
#include "bismuth/renderer.hpp"
#include "bismuth/shaperenderer.hpp"
#include "bismuth/tiledmap.hpp"
#include "glm/gtc/constants.hpp"
#include <vector>
class PlayerSystem{

    public:
        PlayerSystem();
        ~PlayerSystem();
        void update(float dt, bi::TiledObject player, bi::Renderer& renderer, bi::ShapeRenderer& shaperenderer, glm::vec2 mouse);
    private:
        glm::vec2 newPos{0,0};
        glm::vec2 direction{0,0};
        std::vector<glm::vec2> directionQueue;
        float speed = 100;
        bool hit = false;


};

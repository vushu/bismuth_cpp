#pragma once
#include "bismuth/keylistener.hpp"
#include "bismuth/renderer.hpp"
#include "bismuth/shaperenderer.hpp"
#include "bismuth/tiledmap.hpp"
#include "glm/gtc/constants.hpp"
class PlayerSystem{

    public:
        PlayerSystem();
        ~PlayerSystem();
        void update(float dt, bi::TiledObject player, bi::Renderer& renderer, bi::ShapeRenderer& shaperenderer);
    private:
        glm::vec2 newPos{0,0};
        glm::vec2 direction{0,0};
        float speed = 100;


};

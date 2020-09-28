#pragma once
#include "bismuth/keylistener.hpp"
#include "bismuth/particle.hpp"
#include "bismuth/particleemitter.hpp"
#include "bismuth/renderer.hpp"
#include "bismuth/shaperenderer.hpp"
#include "bismuth/tiledmap.hpp"
#include "glm/gtc/constants.hpp"
#include <queue>
class PlayerSystem{

    public:
        PlayerSystem();
        ~PlayerSystem();
        void update(float dt, bi::TiledObject player, bi::Renderer& renderer, bi::ShapeRenderer& shaperenderer, glm::vec2 mouse, int smokeTexId);
    private:

        glm::vec2 zero {0,0};
        float accDt;

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
            //ParticleEmitter(glm::vec2 pos, glm::vec2 vel, unsigned int nparticles) :
        bi::ParticleEmitter particleemitter { 500 };
        bi::ParticleEmitter particleemitter2 { 100 };
        //void initParticle();
        //void particleLifeCheck(float dt);
        //void drawParticles(float dt, bi::Renderer& renderer);
        //unsigned int nr_particles = 120;
        //std::vector<Particle> particles;
        //unsigned int lastUsedParticle = 0;
        //unsigned int firstUnusedParticle();

        //void respawnParticle(Particle& particle, glm::vec2 offset);


};

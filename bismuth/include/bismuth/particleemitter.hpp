#pragma once
#include <bismuth/renderer.hpp>
#include <bismuth/particle.hpp>
#include <glm/glm.hpp>
#include <vector>
namespace bi{
    class ParticleEmitter{
        public:
            // constructors, asssignment, destructor
            ParticleEmitter(unsigned int nparticles) :
                nr_particles(nparticles) { }
            ~ParticleEmitter();

            void emit(float dt, glm::vec2 position, glm::vec2 velocity, glm::vec4 color, int textureId, int tileNumber, glm::vec2 tilesize, glm::vec2 particleSize, Renderer& renderer);
            void init(float lifeTime = 1.0f);
            void setLife(float lifeTime);
        private:
            glm::vec2 position, velocity;
            float life = 1.0f;
            std::vector<Particle> particles;

            unsigned int nr_particles = 0;
            unsigned int lastUsedParticle = 0;
            unsigned int firstUnusedParticle();
            void respawnParticle(Particle& particle);
            void particleLifeCheck(float dt);
    };
}

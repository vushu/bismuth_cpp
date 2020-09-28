#include <bismuth/assetmanager.hpp>
#include <bismuth/particleemitter.hpp>
#include <bismuth/renderer.hpp>
using namespace bi;
ParticleEmitter::~ParticleEmitter() {}

void ParticleEmitter::init(float lifeTime) {
    this->life = lifeTime;
    for (unsigned int i = 0; i < nr_particles; ++i){
        Particle p (0.0f);
        particles.push_back(std::move(p));
    }

}

void ParticleEmitter::emit(float dt, glm::vec2 position, glm::vec2 velocity, glm::vec4 color, int textureId, int tileNumber, glm::vec2 tilesize, glm::vec2 particleSize, Renderer& renderer) {
    this->position = position;
    this->velocity = velocity;
    renderer.setAdditiveBlend();
    auto texCoord = bi::assetManager().getTexture(textureId).getTexCoords(tileNumber, tilesize);
    for (Particle& p : this->particles) {
        if (p.life > 0.0f) {
            renderer.drawTexture(p.position, particleSize, color, textureId, 0, texCoord);
        }
    }
    accDt += dt;
    renderer.endFlushBegin();
    renderer.setDefaultBlend();
    // 60 fps
    if (accDt >= 1.0f/60.0f) {
        particleLifeCheck(1.0f/60.0f);
        accDt -= 1.0f/60.0f;
        if (accDt < 0) {
            accDt = 0;
        }
    }
}

unsigned int ParticleEmitter::firstUnusedParticle() {
    // search from last used particle, this will usually return almost instantly
    for (unsigned int i = lastUsedParticle; i < nr_particles; ++i) {
        if (particles[i].life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // otherwise, do a linear search
    for (unsigned int i = 0; i < lastUsedParticle; ++i) {
        if (particles[i].life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    // override first particle if all others are alive
    lastUsedParticle = 0;
    return 0;
}

void ParticleEmitter::particleLifeCheck(float dt) {
    unsigned int nr_new_particles = 2;
    // add new particles
    for (unsigned int i = 0; i < nr_new_particles; ++i)
    {
        int unusedParticle = firstUnusedParticle();
        Particle& particle =  particles[unusedParticle];
        respawnParticle(particle);
    }
    // update all particles
    for (unsigned int i = 0; i < nr_particles; ++i)
    {
        Particle &p = particles[i];
        p.life -= dt; // reduce life
        if (p.life > 0.0f)
        {   // particle is alive, thus update
            p.position -= p.velocity * dt;
            p.color.a -= dt * 2.5f;
        }
    }
}

void ParticleEmitter::respawnParticle(Particle& particle) {
    float random = ((rand() % 100) - 50) / 10.0f;
    float rColor = 0.5f + ((rand() % 100) / 100.0f);
    particle.position = position + random;
    particle.color = glm::vec4(rColor, rColor, rColor, 1.0f);
    particle.life = life;
    particle.velocity = velocity;
}

void ParticleEmitter::setLife(float lifeTime)
{
    this->life = lifeTime;
}




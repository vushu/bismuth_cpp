#pragma once
#include <glm/glm.hpp>
class Particle{
    public:
        Particle(float lifeTime = 0.0f) : life(lifeTime) {}
        ~Particle();

        glm::vec2 position{0,0}, velocity{0,0};
        float life{0.0f};
        glm::vec4 color{0,0,0,0};

    private:

};

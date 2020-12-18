#include "bismuth/particleemitter.hpp"
#include "glm/fwd.hpp"
class DustTrail {
public:
    // constructors, asssignment, destructor
    DustTrail();
    ~DustTrail();
    void update(float dt, glm::vec2 position, glm::vec2 direction);

private:
    bi::ParticleEmitter particleemitter { 80 };
    int textureId, tileNumber;
    glm::vec2 position;
    glm::vec4 color { 0.1f, 0.2f, 0.5f, 0.5f };
    glm::vec2 tilesize { 16.0f, 16.0f };
    glm::vec2 particleSize { 10.0f, 10.0f };
    glm::vec2 left { -1, 0 };
    glm::vec2 right { 1, 0 };
    glm::vec2 up { 0, -1 };
    glm::vec2 down { 0, 1 };
    glm::vec2 zero { 0, 0 };
    std::string smokeImage = "resources/assets/images/smoke.png";
    void emitLeft(float dt, glm::vec2 position);
    void emitRight(float dt, glm::vec2 position);
    void emitUp(float dt, glm::vec2 position);
    void emitDown(float dt, glm::vec2 position);
};

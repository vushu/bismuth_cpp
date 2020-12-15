#include "dust_trail.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/logging.hpp"

DustTrail::DustTrail()
{
    this->textureId = bi::ioManager().assetmanager->loadTexture(smokeImage);
    bi::log("textureId :",textureId);
    particleemitter.init();
}

DustTrail::~DustTrail() {

}

void DustTrail::update(float dt, glm::vec2 position, glm::vec2 direction)
{
    if (direction == left) {
        emitLeft(dt, position);
    } else if (direction == right) {
        emitLeft(dt, position);
    } else if (direction == up) {
        emitLeft(dt, position);
    } else if (direction == down) {
        emitLeft(dt, position);
    }
}

void DustTrail::emitLeft(float dt, glm::vec2 position)
{
    particleemitter.emit(dt, position, left, { -4, 0 }, color, textureId, tileNumber, tilesize, particleSize, true);
}

void DustTrail::emitRight(float dt, glm::vec2 position)
{
    particleemitter.emit(dt, position, right, { -4, 0 }, color, textureId, tileNumber, tilesize, particleSize, true);
}

void DustTrail::emitUp(float dt, glm::vec2 position)
{
    particleemitter.emit(dt, position, up, { -4, 0 }, color, textureId, tileNumber, tilesize, particleSize, true);
}

void DustTrail::emitDown(float dt, glm::vec2 position)
{
    particleemitter.emit(dt, position, down, { -4, 0 }, color, textureId, tileNumber, tilesize, particleSize, true);
}

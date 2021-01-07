#include "dust_trail.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/logging.hpp"

DustTrail::DustTrail()
{
    this->textureId = bi::ioManager().assetmanager->loadTexture(smokeImage);
    bi::log("textureId :", textureId);
    particleemitter.init();
}

DustTrail::~DustTrail()
{
}

void DustTrail::update(float dt, glm::vec2 position, glm::vec2 direction)
{

    if (direction == left) {
        emitLeft(dt, position);
    } else if (direction == right) {
        emitRight(dt, position);
    } else if (direction == up) {
        emitUp(dt, position);
    } else if (direction == down) {
        emitDown(dt, position);
    }

    if (direction == zero) {
        particleemitter.setLife(0.0f);
        particleemitter.emit(dt, position, direction, { -4, 0 }, color, textureId, tileNumber, tilesize, particleSize, true);
    } else {
        particleemitter.setLife(1.0f);
    }
}

void DustTrail::emitLeft(float dt, glm::vec2 position)
{
    glm::vec2 pos = position - glm::vec2 { 0, 4 };
    particleemitter.emit(dt, pos, left, { -4, 0 }, color, textureId, tileNumber, tilesize, particleSize, true);
}

void DustTrail::emitRight(float dt, glm::vec2 position)
{
    glm::vec2 pos = position - glm::vec2 { 5, 4 };
    particleemitter.emit(dt, pos, right, { 20, 0 }, color, textureId, tileNumber, tilesize, particleSize, true);
}

void DustTrail::emitUp(float dt, glm::vec2 position)
{
    glm::vec2 pos = position - glm::vec2 { 4, 0 };
    particleemitter.emit(dt, pos, up, { -12, 0 }, color, textureId, tileNumber, tilesize, particleSize, true);
}

void DustTrail::emitDown(float dt, glm::vec2 position)
{
    glm::vec2 pos = position - glm::vec2 { 4, 0 };
    particleemitter.emit(dt, pos, down, { -12, 0 }, color, textureId, tileNumber, tilesize, particleSize, true);
}

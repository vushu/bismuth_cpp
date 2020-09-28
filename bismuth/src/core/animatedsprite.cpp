#include "bismuth/assetmanager.hpp"
#include <bismuth/animatedsprite.hpp>
#include <bismuth/renderer.hpp>
using namespace bi;

AnimatedSprite::~AnimatedSprite() {}


void AnimatedSprite::draw(Renderer& renderer, glm::vec2 pos, glm::vec2 size, glm::vec4 color, float angle, float dt, float frameTime){
    timer += dt;
    auto texCoords = bi::assetManager().getTexture(this->textureId).getTexCoords(tileNumbers.at(index), size);
    renderer.drawTexture(pos, size, color, textureId, angle, texCoords);

    if (this->timer > frameTime) {
        timer = 0;
        index++;
        if (index == tileNumbers.size() - 1) {
            index = 0;
        }
    }
}

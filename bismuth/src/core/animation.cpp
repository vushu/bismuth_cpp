#include <bismuth/iomanager.hpp>
#include <bismuth/animation.hpp>
#include <bismuth/renderer.hpp>
using namespace bi;

Animation::~Animation() {}


void Animation::draw(Renderer& renderer, float dt, float angle){
    timer += dt;
    auto texCoords = bi::ioManager().assetmanager->getTexture(this->textureId).getTexCoords(tileNumbers.at(index), size);
    renderer.drawTexture(position, size, color, textureId, angle, texCoords);

    if (this->timer > frameTime) {
        timer = 0;
        index++;
        if (index == tileNumbers.size() - 1) {
            index = 0;
        }
    }
}

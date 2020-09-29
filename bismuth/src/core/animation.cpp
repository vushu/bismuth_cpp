#include <bismuth/iomanager.hpp>
#include <bismuth/animation.hpp>
#include <bismuth/renderer.hpp>
using namespace bi;


Animation::Animation(int texId, std::vector<int> tileNr, glm::vec2 size, glm::vec4 color, float frameTime){
    this->textureId = texId;
    this->tileNumbers = tileNr;
    this->color = color;
    this->frameTime = frameTime;
}

Animation::~Animation() {}

void Animation::draw(float dt, glm::vec2 pos, float angle){
    timer += dt;
    auto texCoords = bi::ioManager().assetmanager->getTexture(this->textureId).getTexCoords(tileNumbers.at(index), size);
    bi::ioManager().renderer->drawTexture(pos, size, color, textureId, angle, texCoords);

    if (this->timer > frameTime) {
        timer = 0;
        index++;
        if (index == tileNumbers.size() - 1) {
            index = 0;
        }
    }
}

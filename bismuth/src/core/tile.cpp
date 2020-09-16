#include "bismuth/logging.hpp"
#include <bismuth/tile.hpp>
using namespace bi;

Tile::~Tile() {}

void Tile::setup() {

    //id is 1 index, but we want it 0 indexed which is why id-1
    int posX = (id-1) % (int) (imageSize.x / tileSize.x);
    int posY = (int) ((id-1) / (imageSize.x / tileSize.x));

    //bi::log("tileID: ",id);

    posX = posX * tileSize.x;
    posY = posY * tileSize.y;
    //bi::log("posX", posX);
    //bi::log("posY", posY);

    this->texCoords = {
        glm::vec2{(float)(posX + tileSize.x) / imageSize.x, (float)(posY + tileSize.y) / imageSize.y}, //BR
        glm::vec2{(float)(posX + tileSize.x) / imageSize.x, (float)posY / imageSize.y}, //TR
        glm::vec2{(float)posX / imageSize.x, (float) posY / imageSize.y}, //TL
        glm::vec2{(float)posX / imageSize.x, ((float) posY + tileSize.y) / imageSize.y}  //BL
    };
}

void Tile::animate() {
    bi::log("animated sprite not implemented");
}

std::array<glm::vec2, 4> Tile::getTexCoords() {

    return this->texCoords;
}

glm::vec2 Tile::getPosition() {
    return this->position;
}

unsigned int Tile::getTextureId() {
    return this->texId;
}

unsigned int Tile::getId() {
    return this->id;
}

glm::vec2 Tile::getTileSize() {
    return this->tileSize;
}

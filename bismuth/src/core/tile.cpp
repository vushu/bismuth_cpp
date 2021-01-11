#include "bismuth/logging.hpp"
#include <bismuth/tile.hpp>
using namespace bi;

Tile::~Tile() {}

void Tile::setup() {
    //id is 1 index, but we want it 0 indexed which is why id-1
    int cellX = id % (int) (imageSize.x / tileSize.x);
    int cellY = (int) (id / (imageSize.x / tileSize.x));
    //tileCell = { cellX, cellY};

    int posX = cellX * tileSize.x;
    int posY = cellY * tileSize.y;

    tileCell = {(float)posX / imageSize.x, (float) posY / imageSize.y}, //TL

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

void Tile::setPosition(glm::vec2 pos) {
    this->position = pos;
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
glm::vec2 Tile::getTileCell() {
    return this->tileCell;
}

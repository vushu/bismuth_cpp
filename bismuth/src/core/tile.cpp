#include "bismuth/logging.hpp"
#include <bismuth/tile.hpp>
#include <limits>
using namespace bi;

Tile::~Tile() {}

void Tile::setup() {

    int numberOfTiles = (int)(imageSize.x / tileSize.x) * (imageSize.y / tileSize.y);

    int posX = 0;
    int posY = 0;
    // Reached max tile
    if (numberOfTiles == id)
    {
        posX = (id - 1) % numberOfTiles;
        posY = (int)((id - 1) / (imageSize.y / tileSize.y));
    }
    else
    {
        posX = id % numberOfTiles;
        posY = (int)(id / (imageSize.y / tileSize.y));
    }
    posX = posX * tileSize.x;
    posY = posY * tileSize.y;

    this->texCoords = {
        glm::vec2{(float)(posX + tileSize.x) / imageSize.x, (float)(posY + tileSize.y) / imageSize.y}, //BR
        glm::vec2{(float)(posX + tileSize.x) / imageSize.x, (float)posY / imageSize.y},                //TR
        glm::vec2{(float)posX / imageSize.x, (float)posY / imageSize.y},                               //TL
        glm::vec2{(float)posX / imageSize.x, ((float)posY + tileSize.y) / imageSize.y}                 //BL
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
    return {static_cast<int>(this->position.x/tileSize.x), static_cast<int>(this->position.y/tileSize.y)};
}

bool Tile::isEmpty()  {
    return id == std::numeric_limits<unsigned int>::max();
}

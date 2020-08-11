#include <bismuth/sprite.hpp>
#include <memory>

using namespace bi;

Sprite::Sprite(std::shared_ptr<Texture> texture) {
    this->texture = std::move(texture);
    this->texCoords.push_back(glm::vec2(1,1));
    this->texCoords.push_back(glm::vec2(1,0));
    this->texCoords.push_back(glm::vec2(0,0));
    this->texCoords.push_back(glm::vec2(0,1));
}

Sprite::~Sprite() {}

int Sprite::getTextureId() {
    if (this->texture)
        return texture->textureId;
    else return -1;
}

void Sprite::setTexture(Texture& texture) {
}

void Sprite::setTexCoords(std::vector<glm::vec2>& texCoords) {
    this->texCoords = std::move(texCoords);
}

std::vector<glm::vec2> Sprite::getTexCoords() {
    return this->texCoords;
}

std::shared_ptr<Texture> Sprite::getTexture() {
    return this->texture;
}


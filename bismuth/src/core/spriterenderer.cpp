#include <bismuth/logging.hpp>
#include <bismuth/spriterenderer.hpp>

using namespace bi;

SpriteRenderer::SpriteRenderer(std::unique_ptr<Sprite> sprite) {
    this->mSprite = std::move(sprite);
    this->color = glm::vec4(1,1,1,1);
    this->position = glm::vec2(0,0);
    this->scale = glm::vec2(225,225);
}

SpriteRenderer::~SpriteRenderer() {}


void SpriteRenderer::setColor(glm::vec4 color) {
    bi::log("setting color");
    this->color = color;
    this->isDirty = true;
}

std::vector<glm::vec2> SpriteRenderer::getTexCoords() {
    return this->mSprite->getTexCoords();
}

void SpriteRenderer::setClean() {
    this->isDirty = false;
}

std::shared_ptr<Texture> SpriteRenderer::getTexture() {
    return this->mSprite->getTexture();
}

void SpriteRenderer::setPosition(glm::vec2 position) {
    //if (this->position != position) {
    this->position = position;
    this->isDirty = true;
    //}
}

void SpriteRenderer::setScale(glm::vec2 scale) {
    if (this->scale != scale) {
        this->scale = scale;
        isDirty = true;
    }
}

void SpriteRenderer::initTexture() {
    if (this->mSprite->getTexture() != nullptr)
        this->mSprite->getTexture()->init();
}



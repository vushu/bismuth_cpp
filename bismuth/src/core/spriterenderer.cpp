#include <glm/ext/matrix_transform.hpp>
#include <bismuth/logging.hpp>
#include <bismuth/spriterenderer.hpp>
#include <glm/glm.hpp>

using namespace bi;

SpriteRenderer::SpriteRenderer(std::unique_ptr<Sprite> sprite) {
    this->mSprite = std::move(sprite);
    this->color = glm::vec4(1,1,1,1);
    this->position = glm::vec2(0,0);
    this->angleDegrees = 0.0f;
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
    this->position = position;
    this->isDirty = true;
}

void SpriteRenderer::setScale(glm::vec2 scale) {
    if (this->scale != scale) {
        this->scale = scale;
        isDirty = true;
    }
}
void SpriteRenderer::setTextureCoords(std::vector<glm::vec2> coords) {
    isDirty = true;
}

void SpriteRenderer::setRotation(float angleDegrees) {
    this->angleDegrees = angleDegrees;
    isDirty = true;
}

void SpriteRenderer::initTexture() {
    if (this->mSprite->getTexture() != nullptr)
        this->mSprite->getTexture()->init();
}

std::string SpriteRenderer::getTextureFilePath() {
    return this->mSprite->getTextureFilePath();
}



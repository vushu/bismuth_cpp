#include <bismuth/bismuth.hpp>
#include "playerball.hpp"

PlayerBall::~PlayerBall(){}

void PlayerBall::draw(bi::Renderer& renderer) {
    renderer.drawTexture(mPosition, this->mSize, this->mColor, this->mTextureId, 0.0f);
}

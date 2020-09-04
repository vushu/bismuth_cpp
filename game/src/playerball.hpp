#pragma once
#include "bismuth/logging.hpp"
#include <bismuth/renderer.hpp>
#include <string>

class PlayerBall{
    public:
        // constructors, asssignment, destructor
        PlayerBall(int texId): mTextureId(texId) {}
        ~PlayerBall();
        void draw(bi::Renderer& renderer);

        glm::vec2 mPosition = {100,200};
        glm::vec2 mSize {30.0f,30.0f};
        glm::vec4 mColor {1,1,1,1};
        float mAngle = 0.0f;
        int mTextureId;

    private:
};

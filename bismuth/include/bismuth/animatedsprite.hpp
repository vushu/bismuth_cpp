#pragma once
#include <bismuth/renderer.hpp>
#include <vector>
namespace bi {
    class AnimatedSprite{
        public:
            // constructors, asssignment, destructor
            AnimatedSprite(int texId, std::vector<int> tileNr): textureId(texId), tileNumbers(tileNr) {}
            ~AnimatedSprite();
            void draw(Renderer& renderer, glm::vec2 pos, glm::vec2 size, glm::vec4 color, float angle, float dt, float frameTime);

        private:
            int textureId;
            std::vector<int> tileNumbers;
            float timer = 0.0f;
            int index = 0;


    };
}

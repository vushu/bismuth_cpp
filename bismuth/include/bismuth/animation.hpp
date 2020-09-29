#pragma once
#include <bismuth/renderer.hpp>
#include <vector>
namespace bi {
    class Animation {
        public:
            // constructors, asssignment, destructor
            Animation(int texId, std::vector<int> tileNr): textureId(texId), tileNumbers(tileNr) {}
            ~Animation();
            void draw(Renderer& renderer,float dt, float angle);

        private:
            int textureId;
            std::vector<int> tileNumbers;
            float timer = 0.0f;
            int index = 0;

            glm::vec2 position;
            glm::vec2 size;
            glm::vec4 color;
            float frameTime;


    };
}

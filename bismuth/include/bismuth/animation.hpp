#pragma once
#include <bismuth/renderer.hpp>
#include <vector>
namespace bi {
    class Animation {
        public:
            Animation(std::string name,int texId, std::vector<int> tileNumbers, glm::vec2 size, glm::vec4 color, float frameTime);
            ~Animation();
            void draw(float dt, glm::vec2 pos, float angle);
            std::string name;

        private:
            int textureId;
            std::vector<int> tileNumbers;
            float timer = 0.0f;
            unsigned int index = 0;
            glm::vec2 size;
            glm::vec4 color;
            float frameTime;

    };
}

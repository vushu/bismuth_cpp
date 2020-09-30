#pragma once
#include <map>
#include <bismuth/animation.hpp>
namespace bi {
    class AnimatedSprite{
        public:
            // constructors, asssignment, destructor
            AnimatedSprite();
            ~AnimatedSprite();
            void addAnimation(Animation animation);
            void addAnimation(std::string name, int texId, std::vector<int> tileNumbers, glm::vec2 size, glm::vec4 color, float frameTime);
            void play(std::string name, float dt, glm::vec2 position, float angle = 0.0f);

        private:
            std::map<std::string, Animation> animations;


    };
}

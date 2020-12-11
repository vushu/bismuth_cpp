#pragma once
#include <bismuth/animatedsprite.hpp>
namespace bi  {
    class Player{
        public:
            // constructors, asssignment, destructor
            Player();
            ~Player();

            void init();
            void play();
            void playAnimationRight(float dt, glm::vec2 position);
            void playAnimationLeft(float dt, glm::vec2 position);
            void playAnimationUp(float dt, glm::vec2 position);
            void playAnimationDown(float dt, glm::vec2 position);
        private:
            int drillTexId;
            std::string drillPath = "resources/assets/images/drill.png";
            AnimatedSprite animatedSprite;
            void createAnimatedSprite();
    };
}

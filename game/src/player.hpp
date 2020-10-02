#pragma once
#include <bismuth/animatedsprite.hpp>
namespace bi  {
    class Player{
        public:
            // constructors, asssignment, destructor
            Player();
            ~Player();

            void init();
        private:
            int drillTexId;
            std::string drillPath = "resources/assets/images/drill.png";
            AnimatedSprite animatedSprite;
            void createAnimatedSprite();
    };
}

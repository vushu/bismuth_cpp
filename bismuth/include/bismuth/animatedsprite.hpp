#pragma once
#include <map>
#include <bismuth/animation.hpp>
namespace bi {
    class AnimatedSprite{
        public:
            // constructors, asssignment, destructor
            AnimatedSprite();
            AnimatedSprite(const AnimatedSprite&);
            AnimatedSprite& operator=(const AnimatedSprite&);
            ~AnimatedSprite();
            void play(std::string name);

        private:
            std::map<std::string, Animation> animations;

    };
}

#pragma once
#include "bismuth/sound.hpp"
#include <bismuth/scene.hpp>
class FirstScene : public bi::Scene {
    public:
        // constructors, asssignment, destructor
        FirstScene();
        ~FirstScene();
        void init();
        void update(float dt);
        void close();
        void start();
    private:
        std::shared_ptr<bi::Sound> levelSound;

};

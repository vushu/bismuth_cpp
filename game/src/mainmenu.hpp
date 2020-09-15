#pragma once
#include <bismuth/sound.hpp>
#include <bismuth/scene.hpp>
class MainMenuScene : public bi::Scene {
    public:
        // constructors, asssignment, destructor
        MainMenuScene ();
        ~MainMenuScene ();
        void update(float dt);
        void init();
        void start();
        void close();
    private:
        float accTime = 0.0;
        std::shared_ptr<bi::Sound> mainMenuMusic;
        std::shared_ptr<bi::Sound> tower;
        unsigned int textureId = 0;
        void setStyle();
        void drawMenu();


};

#pragma once

#include <bismuth/sound.hpp>
#include <bismuth/scene.hpp>

class MainMenuScene : public bi::Scene {
public:
    // constructors, asssignment, destructor
    MainMenuScene();

    ~MainMenuScene();

    void update(float dt);

    void render(float dt);
   
    void processInput(float dt);

    void init();

    void start();

    void close();

private:
    float accTime = 0.0;
    std::shared_ptr<bi::Sound> mainMenuMusic;
    std::shared_ptr<bi::Sound> tower;
    int buttonWidth = 100, buttonHeight = 35;
    int menuWidth = buttonWidth + 15, menuHeight = buttonHeight * 3 + 25;
    unsigned int textureId = 0;

    void setStyle();

    void drawMenu();


};

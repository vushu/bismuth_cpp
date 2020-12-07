#pragma once
#include <bismuth/scene.hpp>
#include <bismuth/font.hpp>
#include <memory>



class MainMenuSceneB : public bi::Scene {

public:
    // constructors, asssignment, destructor
    MainMenuSceneB();
    ~MainMenuSceneB();

    void update(float dt);
    void init();
    void start();
    void close();

private:
    std::unique_ptr<bi::Font> font;
};

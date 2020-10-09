#pragma once
#include <bismuth/scene.hpp>

class MainMenuSceneB : public bi::Scene {

public:
    // constructors, asssignment, destructor
    MainMenuSceneB();
    ~MainMenuSceneB();

    void update();
    void init();
    void start();
    void close();

private:
};

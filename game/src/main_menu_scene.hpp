#pragma once
#include <bismuth/scene.hpp>
#include <nanovg/nanovg.h>
//#define NANOVG_GLES3_IMPLEMENTATION
//#include <nanovg/nanovg_gl.h>
//#include <nanovg/nanovg_gl_utils.h>



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
    NVGcontext* vg = nullptr;
};

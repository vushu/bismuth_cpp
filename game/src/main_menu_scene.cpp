#include "main_menu_scene.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include <nanovg/nanovg.h>
#include <stdexcept>
//#define NANOVG_GLES3_IMPLEMENTATION
//#include <nanovg/nanovg_gl.h>
//#include <nanovg/nanovg_gl_utils.h>

//#define NK_IMPLEMENTATION
//#include <nuklear/nuklear.h>

MainMenuSceneB::MainMenuSceneB() { }

MainMenuSceneB::~MainMenuSceneB()
{
    bi::log("deleting nvg instance");
}

void MainMenuSceneB::update(float dt)
{
    if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_RIGHT)) {
        nextScene = "firstscene";
    }
    getRenderer().clear();
    float pxRatio = getWindow().maxWidth / getWindow().maxHeight;

    //getShapeRenderer().drawLine({100,10}, {200,10}, {1,1,0,1});
    //getShapeRenderer().endFlushBegin();

    /*
    nvgBeginFrame(vg, getWindow().maxWidth, getWindow().maxHeight, pxRatio);
    nvgSave(vg);

    nvgBeginPath(vg);
    nvgCircle(vg, 100, 100, 40);

    nvgRect(vg, 100, 100, 120, 30);
    nvgFillColor(vg, nvgRGBA(255, 192, 0, 255));
    nvgFill(vg);

    nvgRestore(vg);
    nvgEndFrame(vg);
*/
}

void MainMenuSceneB::init()
{
    //vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

    //if (vg == nullptr) {
        //throw std::runtime_error("Failed to create nanovg instance");
    //}

    //bi::log("Successfully created nanovg instance");
}

void MainMenuSceneB::start()
{
}

void MainMenuSceneB::close()
{
    glEnable(GL_BLEND);
    bi::log("closing mainmenuB");
}
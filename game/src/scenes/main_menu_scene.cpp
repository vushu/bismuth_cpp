#include "main_menu_scene.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include <stdexcept>
#include <imgui/imgui.h>

MainMenuSceneB::MainMenuSceneB() { }

MainMenuSceneB::~MainMenuSceneB()
{
}

void MainMenuSceneB::update(float dt)
{
    if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_RIGHT)) {
        nextScene = "firstscene";
    }
    //getRenderer().clear();

    //getGuiManager().beginDraw();
    //getGuiManager().showFPS();
    //getGuiManager().endDraw();
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

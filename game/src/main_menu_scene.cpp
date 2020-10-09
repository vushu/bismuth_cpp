#include "main_menu_scene.hpp"
#include <stdexcept>
#include "bismuth/logging.hpp"
#include <nanovg/nanovg.h>
#define NANOVG_GLES3_IMPLEMENTATION
#include <nanovg/nanovg_gl.h>
#include <nanovg/nanovg_gl_utils.h>



MainMenuSceneB::MainMenuSceneB() {}

MainMenuSceneB::~MainMenuSceneB() {
    bi::log("deleting nvg instance");
    nvgDeleteGLES3(vg);
}

void MainMenuSceneB::update(float dt) {
    getRenderer().clear();
    float pxRatio = getWindow().maxWidth / getWindow().maxHeight;

    nvgBeginFrame(vg, getWindow().maxWidth, getWindow().maxHeight, pxRatio);

    nvgBeginPath(vg);

    nvgRect(vg, 100,100,120,30);
    nvgFillColor(vg, nvgRGBA(255, 192, 0, 255));
    nvgFill(vg);

    nvgEndFrame(vg);



}

void MainMenuSceneB::init()
{
    vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

    if (vg == nullptr) {
        throw std::runtime_error("Failed to create nanovg instance");
    }

    bi::log("Successfully created nanovg instance");

}

void MainMenuSceneB::start() {

}

void MainMenuSceneB::close() {
}

#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include <GLFW/glfw3.h>

void bi::KeyListener::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (action == GLFW_PRESS) {
        bi::KeyListener::get().keyPressed[key] = true;
    } else if (action == GLFW_RELEASE) {
        bi::KeyListener::get().keyPressed[key] = false;
    }
}

bool bi::KeyListener::isKeyPressed(int keyCode) {
    return get().keyPressed[keyCode];
}

bi::KeyListener::KeyListener() {}

bi::KeyListener::~KeyListener() {}

bi::KeyListener& bi::keyInput() {
    return bi::KeyListener::get();
}

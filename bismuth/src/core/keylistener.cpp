#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <array>
#include <cstring>

void bi::KeyListener::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (action == GLFW_PRESS) {
        bi::KeyListener::get().keyPressed[key] = true;
        bi::KeyListener::get().keyReleased[key] = false;
    } else if (action == GLFW_RELEASE) {
        bi::KeyListener::get().keyReleased[key] = true;
        bi::KeyListener::get().keyPressed[key] = false;
    }
}

bool bi::KeyListener::isKeyReleased(int keyCode) {
    bool keyReleased = get().keyReleased[keyCode];
    if (keyReleased) {
        get().keyReleased[keyCode] = false;
    }
    return keyReleased;
}

bool bi::KeyListener::isKeyPressed(int keyCode) {
    return get().keyPressed[keyCode];
}

bi::KeyListener::KeyListener() {}

bi::KeyListener::~KeyListener() {}

void bi::KeyListener::reset() {
    std::memset(&get().keyReleased, 0 , sizeof(get().keyReleased));
}

bi::KeyListener& bi::keyInput() {
    return bi::KeyListener::get();
}

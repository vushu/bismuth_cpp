#include <bismuth/mouselistener.hpp>
#include <GLFW/glfw3.h>
using namespace bi;

MouseListener::MouseListener() {}

MouseListener::~MouseListener() {}

void MouseListener::mousePosCallback(GLFWwindow* window, double xPos, double yPos) {
    MouseListener::get().lastX = MouseListener::get().xPos;
    MouseListener::get().lastY = MouseListener::get().yPos;
    MouseListener::get().xPos = xPos;
    MouseListener::get().yPos = yPos;
    MouseListener::get().isDragging = MouseListener::get().mouseButtonPressed[0] || MouseListener::get().mouseButtonPressed[1] || MouseListener::get().mouseButtonPressed[2];
}

void MouseListener::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

    if (action == GLFW_PRESS) {
        if (button < MouseListener::numberOfMouseButtons) {
            MouseListener::get().mouseButtonPressed[button] = true;
        }
    }
    else if (action == GLFW_RELEASE) {
        if (button < MouseListener::numberOfMouseButtons) {
            MouseListener::get().mouseButtonPressed[button] = false;
            MouseListener::get().isDragging = false;
        }
    }
}

void MouseListener::mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    MouseListener::get().scrollX = xOffset;
    MouseListener::get().scrollY = yOffset;
}

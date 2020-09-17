#include "bismuth/logging.hpp"
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

float MouseListener::toOrthoX(Camera& camera, int width) {
    float currentX = (MouseListener::get().xPos / (float) width) * 2.0f - 1.0f ;
    glm::vec4 tmp (currentX,0,0,1);
    tmp = camera.inverseViewMatrix * camera.inverseProjectionMatrix * tmp;

    return tmp.x;
}

float MouseListener::toOrthoY(Camera& camera, int height) {
    float currentY = (MouseListener::get().yPos / (float) height) * 2.0f - 1.0f;
    glm::vec4 tmp (0,currentY,0,1);
    tmp = camera.inverseViewMatrix * camera.inverseProjectionMatrix * tmp;
    return camera.height - tmp.y;
    //return tmp.y;

}

bi::MouseListener& bi::mouseInput() {
    return bi::MouseListener::get();
}

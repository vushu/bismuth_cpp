#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>
#include "camera.hpp"
namespace bi {

    class MouseListener{
        public:
            static void mousePosCallback(GLFWwindow* window, double xPos, double yPos);
            static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            static void mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
            static float toOrthoX(int width);
            static float toOrthoY(int height);

            static MouseListener& get() {
                static MouseListener instance;
                return instance;
            }

            static bool mouseButtonDown(int button) {
                if (button < numberOfMouseButtons) {
                    return get().mouseButtonPressed[button];
                }
                return false;
            }


            static const int numberOfMouseButtons = 9;
            bool mouseButtonPressed[numberOfMouseButtons] = {false};
            ~MouseListener();
            double scrollX, scrollY;
            double xPos, yPos;
            bool isDragging;
        private:
            MouseListener();


    };
    MouseListener& mouseInput();
}

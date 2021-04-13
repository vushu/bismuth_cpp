#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>
namespace bi {

    class KeyListener{
        public:
            // constructors, asssignment, destructor
            static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

            static KeyListener& get() {
                static KeyListener instance;
                return instance;
            }

            bool keyPressed[350] = {false};

            bool isKeyPressed(int keyCode);

            bool isKeyReleased(int keyCode);

            ~KeyListener();
        private:
            KeyListener();
            int lastKeyCode = -1;


    };
    KeyListener& keyInput();
}

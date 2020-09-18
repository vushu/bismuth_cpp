#pragma once
#include <GLFW/glfw3.h>
#include <string>
namespace  bi {
    class Window{
        public:
            // constructors, asssignment, destructor
            Window(int width, int height, std::string title);
            ~Window();
            void init();
            bool windowShouldClose();
            void pollEvents();
            void close();
            GLFWwindow* window;
            int width;
            int height;
            void swapBuffers();
            int maxWidth;
            int maxHeight;
            void fullscreen(int width, int height);
            void windowed(int width, int height);

        private:

            void getResolution();
            void setupCallbacks();
            static void resizeWindowCallback(GLFWwindow* window, int width, int height);
            static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
            //void errorCallback(int error, const char* description);
            void configureOpenGL();
            std::string title;
    };
}

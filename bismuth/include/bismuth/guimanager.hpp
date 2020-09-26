#pragma once
#include <bismuth/window.hpp>
namespace bi {
    class GuiManager{
        public:
            // constructors, asssignment, destructor
            GuiManager(Window& win): window(win){}
            ~GuiManager();
            void init();
            void beginDraw();
            void endDraw();
            void showFPS();

        private:
            Window& window;
            bool initialized = false;


    };
}

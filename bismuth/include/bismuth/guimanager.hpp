#pragma once
#include <bismuth/window.hpp>
namespace bi {
    class GuiManager{
        public:
            // constructors, asssignment, destructor
            GuiManager(Window& win): window(win){}
            ~GuiManager();
            void init();
            void newFrame();
            void render();
        private:
            Window& window;


    };
}

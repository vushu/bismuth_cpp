#include <bismuth/keylistener.hpp>
#include "game.hpp"
#include <iostream>
#include <bismuth/window.hpp>
#include <bismuth/logging.hpp>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
MyGame game;

void loop() {
    game.loop();
}
int main() {
    //bi::isLogging = false;
    game.run();
#ifdef __EMSCRIPTEN__
    bi::isLogging = false;
    emscripten_set_main_loop(loop, 0 ,-1);
#endif

}


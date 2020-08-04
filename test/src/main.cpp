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
    game.emLoop();
}
int main() {
    bi::isLogging = true;
    game.run();
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0 ,-1);
#endif

}


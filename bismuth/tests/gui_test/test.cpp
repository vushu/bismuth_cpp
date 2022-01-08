#include <catch2/catch.hpp>
#include "bismuth/logging.hpp"
#include "gui_test.hpp"

GuiTest game;

TEST_CASE("Showing in GUIWindow") {
    //bi::isLogging = false;
    game.run();
}

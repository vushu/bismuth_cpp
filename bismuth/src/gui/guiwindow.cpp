#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include <bismuth/gui/guiwindow.hpp>

void GuiWindow::draw() {
    bi::ioManager().shaperenderer->drawRect(this->position, this->size, bi::color::WHITE).endFlushBegin(true);
    bi::ioManager().shaperenderer->drawRect(this->position, this->size, bi::color::SOFT_BLUE).endFlushBegin();
}

void GuiWindow::handleMouseClick(int action, glm::vec2 position) {
    bi::log("handleMouseClick is not implemented yet");
}

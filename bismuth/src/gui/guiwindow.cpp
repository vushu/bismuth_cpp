#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include <bismuth/gui/guiwindow.hpp>
using namespace bi;


GuiWindow::GuiWindow() {

}

GuiWindow& GuiWindow::setOutlineWidth(float outlineWidth) {
    this->outlineWidth = outlineWidth;
    return *this;
}
void GuiWindow::draw() {
    ioManager().shaperenderer->fill();
    ioManager().shaperenderer->drawRect(this->position, this->size, bi::color::WHITE).endFlushBegin();
    ioManager().shaperenderer->setLineWidth(this->outlineWidth);
    ioManager().shaperenderer->drawRect(this->position, this->size, bi::color::SOFT_BLUE).endFlushBegin();
}

void GuiWindow::handleMouseClick(int action, glm::vec2 position) {
    log("handleMouseClick is not implemented yet");
}

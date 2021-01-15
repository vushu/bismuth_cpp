#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include <bismuth/gui/guiwindow.hpp>
using namespace bi;


GuiWindow::GuiWindow() {

}

GuiWindow& GuiWindow::setSize(glm::vec2 size) {
    this->size = size;
    return *this;
}

GuiWindow& GuiWindow::setPosition(glm::vec2 position) {
    this->position = position;
    return *this;
}

GuiWindow& GuiWindow::setOutlineWidth(float outlineWidth) {
    this->outlineWidth = outlineWidth;
    return *this;
}

GuiWindow& GuiWindow::setBackgroundColor(glm::vec4 color)  {
    this->backgroundColor = color;
    return *this;
}

GuiWindow& GuiWindow::setOutlineColor(glm::vec4 color)  {
    this->outlineColor = color;
    return *this;
}

GuiWindow& GuiWindow::activateCloseButton() {
    this->isCloseButtonActivated = true;
    return *this;
}

void GuiWindow::draw() {
    ioManager().shaperenderer->fill();
    ioManager().shaperenderer->drawRect({ this->position.x + this->size.x - 16.0f, this->position.y + 2}, {16,16}, color::SOFT_MAGENTA);
    ioManager().shaperenderer->drawRect(this->position, this->size, backgroundColor);
    ioManager().renderer->endFlushBegin();
    ioManager().shaperenderer->setLineWidth(this->outlineWidth);
    ioManager().shaperenderer->drawRect(this->position, this->size, outlineColor).endFlushBegin();
}

void GuiWindow::handleMouseClick(int action, glm::vec2 position) {
    log("handleMouseClick is not implemented yet");
}

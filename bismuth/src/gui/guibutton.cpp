#include "bismuth/gui/guibutton.hpp"
#include "bismuth/iomanager.hpp"
using namespace bi;

GuiButton::GuiButton() {}
GuiButton::~GuiButton() {}

GuiButton& GuiButton::setBackgroundColor(glm::vec4 color) {
    this->backgroundColor = color;
    return *this;
}

GuiButton& GuiButton::setPosition(glm::vec2 position) {
    this->position = position;
    return *this;
}

GuiButton& GuiButton::setSize(glm::vec2 size) {
    this->size = size;
    return *this;
}

void GuiButton::draw() {
    ioManager().renderer->drawQuad(this->position, this->size, backgroundColor);
}

#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include <bismuth/gui/guilabel.hpp>
#include <bismuth/font.hpp>
#include <string>
using namespace bi::gui;


GuiLabel::GuiLabel(){}

GuiLabel::~GuiLabel() {}


void GuiLabel::setText(Font* font, std::string text) {
    this->font = font;
    this->text = text;
}

void GuiLabel::draw() {
    ioManager().renderer->drawText(this->text, this->position, *font, this->color, fontScale);
}

bool GuiLabel::handleMouseClick(int action, glm::vec2 position) {
    return isPositionWithinRect(position);
}

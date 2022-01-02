#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include <bismuth/gui/guilabel.hpp>
#include <bismuth/font.hpp>
#include <string>
using namespace bi::gui;


void GuiLabel::setFont(Font *font) {
    this->font = font;
}

void GuiLabel::setText(std::string text) {
    if (!font) {
        log("No font is set for label!");
        return;
    }
    this->text = text;
    size = font->getSizeOfText(this->text, fontScale);
}

void GuiLabel::setText(Font* font,std::string text) {
    setFont(font);
    this->text = text;
    size = font->getSizeOfText(this->text, fontScale);
}


void GuiLabel::draw() {
    if (!font) {
        log("No font is set for label!");
        return;
    }
    ioManager().renderer->drawText(this->text, this->position, *font, this->color, fontScale);
}

void GuiLabel::setColor(glm::vec4 color)  {
    this->color = color;
}

bool GuiLabel::handleMouseClick(int action, glm::vec2 position) {
    return isPositionWithinRect(position);
}

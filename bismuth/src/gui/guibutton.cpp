#include "bismuth/gui/guibutton.hpp"
#include "bismuth/gui/guilabel.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/collision/collision.hpp"
#include "bismuth/mouselistener.hpp"
using namespace bi;
using namespace gui;

GuiButton::GuiButton() {}
GuiButton::~GuiButton() {}

GuiButton& GuiButton::setBackgroundColor(glm::vec4 color) {
    this->backgroundColor = color;
    return *this;
}

GuiButton& GuiButton::setSize(glm::vec2 size) {
    this->size = size;
    return *this;
}

GuiButton& GuiButton::setFont(Font* font) {
    this->font = font;
    guiLabel.setFont(font);
    return *this;
}

GuiButton& GuiButton::setTextColor(glm::vec4 color) {
    guiLabel.setColor(color);
    return *this;
}

GuiButton& GuiButton::setText(std::string text) {
    if(!this->font){
        log("Failed to set text setFont first!");
        return *this;
    }
    guiLabel.setPosition(position);
    guiLabel.setText(text);
    if (size == glm::vec2 {0,0}) {
        this->size = guiLabel.size;
    }
    guiLabel.positionCenterTo(position, size);
    return *this;
}

GuiButton& GuiButton::addLabel(GuiElement* guiLabel) {
    guiLabel->parent = this;
    this->children.push_back(guiLabel);
    return *this;
}

void GuiButton::draw() {

    ioManager().renderer->drawQuad(this->position, this->size, outlineColor);
    ioManager().renderer->drawQuad(this->position + outlineThickness, this->size - outlineThickness * 2, backgroundColor);

    if (font) {
        guiLabel.positionCenterTo(position, size);
        guiLabel.draw();
    }

    for (auto& child : children) {
        child->draw();
    }
}


bool GuiButton::mouseClicked() {
    if (bi::mouseInput().mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT) && !this->isPressed){
        if (this->handleMouseClick(GLFW_MOUSE_BUTTON_LEFT, bi::mouseInput().getPosition())) {
            this->isPressed = true;
            return isPressed;
        }
    }
    return false;
}

bool GuiButton::mouseReleased() {

    if (!isPressed) {
        mouseClicked();
    }

    else if (!bi::mouseInput().mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT) && this->isPressed){

        this->isPressed = false;
        if (this->handleMouseClick(GLFW_MOUSE_BUTTON_LEFT, bi::mouseInput().getPosition())) {
            return true;
        }
    }
    return false;
}

bool GuiButton::handleMouseClick(int action, glm::vec2 position) {
    return action == GLFW_MOUSE_BUTTON_LEFT && collision::isPositionWithinRect(position, this->position, this->size);
}


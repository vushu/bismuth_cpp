#include "bismuth/gui/guibutton.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/collision/collision.hpp"
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

GuiButton& GuiButton::addLabel(GuiLabel* guiLabel) {
    children.push_back(guiLabel);
    //this->guiLabel = guiLabel;
    return *this;
}

void GuiButton::draw() {

    ioManager().renderer->drawQuad(this->position, this->size, backgroundColor);

    for(auto& child : children) {
        child->draw();
    }


}

bool GuiButton::handleMouseClick(int action, glm::vec2 position) {
    return action == GLFW_MOUSE_BUTTON_LEFT && collision::isPositionWithinRect(position, this->position, this->size);
}

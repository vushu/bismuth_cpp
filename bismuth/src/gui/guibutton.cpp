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

GuiButton& GuiButton::setPosition(glm::vec2 position) {
    this->position = position;
    if (this->guiLabel){
        this->guiLabel->position = this->position;
        this->guiLabel->position.y -= 4;
        this->guiLabel->position.x += 1;
    }
    return *this;
}

GuiButton& GuiButton::setSize(glm::vec2 size) {
    this->size = size;
    return *this;
}

GuiButton& GuiButton::addLabel(GuiLabel* guiLabel) {
    this->guiLabel = guiLabel;
    return *this;
}

void GuiButton::draw() {

    glm::vec2 outline = this->position;
    outline -= glm::vec2{1,1};
    ioManager().renderer->drawQuad(outline, this->size + glm::vec2{1,2}, color::BLACK);
    ioManager().renderer->drawQuad(this->position, this->size, backgroundColor);
    if (guiLabel){
        guiLabel->draw();
    }


}

void GuiButton::handleMouseClick(int action, glm::vec2 position) {
    if (action == GLFW_MOUSE_BUTTON_LEFT && collision::isPositionWithinRect(position, this->position, this->size)){
        this->isPressed = true;
    }
}

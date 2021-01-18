#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/math.hpp"
#include <bismuth/gui/guiwindow.hpp>
using namespace bi;
using namespace gui;


GuiWindow::GuiWindow() {
    this->closeButton.setBackgroundColor(color::CORNFLOWER_BLUE);
    this->closeButton.setSize({16,16});
    this->closeButton.placement = TOP_RIGHT;
    this->children.push_back(&closeButton);
}

GuiWindow& GuiWindow::setSize(glm::vec2 size) {
    this->size = size;
    return *this;
}

GuiWindow& GuiWindow::setPosition(glm::vec2 position) {
    this->position = position;
    for (auto& child : children) {
        switch (child->placement) {
            case TOP_LEFT:
                child->position = math::clamp(this->position, this->position + this->size, child->position);
                break;
            case TOP_RIGHT:
                child->position = math::clamp({this->position.x + this->size.x, this->position.y }, this->position + this->size, child->position);
                break;
            case BOTTOM_LEFT:
                child->position = math::clamp({this->position.x, this->position.y }, this->position + this->size, child->position);
                break;
            case BOTTOM_RIGHT:
                child->position = math::clamp({this->position.x + this->size.x, this->position.y + this->size.y}, this->position + this->size, child->position);
                break;
            default:
                child->position = math::clamp(this->position, this->position + this->size, child->position);
        }
    }
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

GuiWindow& GuiWindow::add(GuiElement* guielement) {
    this->children.push_back(guielement);
    return *this;
}

glm::vec2 GuiWindow::positionBottomRight(glm::vec2 size) {
    return {this->position.x + this->size.x - size.x, this->position.y + this->size.y - size.y};
}

glm::vec2 GuiWindow::positionTopRight(glm::vec2 size) {
    return {this->position.x + this->size.x - size.x, this->position.y + size.y};
}

void GuiWindow::draw() {
    //ioManager().shaperenderer->drawRect({ this->position.x + this->size.x - 16.0f, this->position.y + 2}, {16,16}, color::SOFT_MAGENTA);
    ioManager().renderer->drawQuad(this->position, this->size, backgroundColor);
    ioManager().shaperenderer->setLineWidth(this->outlineWidth);
    ioManager().shaperenderer->drawRect(this->position, this->size, outlineColor).endFlushBegin();
    for (auto& child : children){
        child->draw();
    }
}

void GuiWindow::handleMouseClick(int action, glm::vec2 position) {
    log("handleMouseClick is not implemented yet");
}

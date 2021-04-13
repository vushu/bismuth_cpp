#include "bismuth/assetmanager.hpp"
#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/math.hpp"
#include "bismuth/mouselistener.hpp"
#include <bismuth/gui/guiwindow.hpp>
#include <bismuth/collision/collision.hpp>
using namespace bi;
using namespace gui;


GuiWindow::GuiWindow() {
    this->closeButton.setBackgroundColor(color::SOFT_RED);
    this->closeButton.setSize({10,10});
    this->closeLabel.setText(&ioManager().assetmanager->getDefaultFont(), "X");
    this->closeLabel.fontScale = 0.15f;
    this->closeLabel.setColor(color::WHITE);
    this->closeButton.placement = TOP_RIGHT;
    this->closeLabel.setOffset({0,-2});
    this->closeButton.addLabel(&closeLabel);
}

GuiWindow& GuiWindow::setSize(glm::vec2 size) {
    this->size = size;
    return *this;
}

GuiWindow& GuiWindow::setPosition(glm::vec2 position) {
    this->position = position;
    this->closeButton.setPosition({this->position.x + this->size.x - closeButton.size.x, this->position.y });
    for (auto& child : children) {
        child->setPosition(position);
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

GuiWindow& GuiWindow::activateCloseButton(bool activate)  {
    this->closeButtonActivated = activate;
    return *this;
}
glm::vec2 GuiWindow::positionBottomRight(glm::vec2 size) {
    return {this->position.x + this->size.x - size.x, this->position.y + this->size.y - size.y};
}

glm::vec2 GuiWindow::positionTopRight(glm::vec2 size) {
    return {this->position.x + this->size.x - size.x, this->position.y + size.y};
}

void GuiWindow::draw() {
    if (isClosed)
        return;
    ioManager().renderer->drawQuad(this->position, this->size, backgroundColor);
    ioManager().shaperenderer->setLineWidth(this->outlineWidth);
    ioManager().shaperenderer->drawRect(this->position, this->size, outlineColor).endFlushBegin();

    for (auto& child : children){
        child->draw();
    }
    if (this->closeButtonActivated)
        closeButton.draw();
}

bool GuiWindow::handleMouseClick(int action, glm::vec2 position) {
    if (isClosed) {
        return false;
    }

    if (action == GLFW_MOUSE_BUTTON_LEFT){
        if (isPositionWithinRect(position)) {

            isFocused = true;
            if(closeButtonActivated && closeButton.handleMouseClick(action, position))
            {
                this->isClosed = true;
            }
        }
        else  {

            isFocused = false;
        }
    }
    return isFocused;
}

bool GuiWindow::mouseClicked() {
    if (bi::mouseInput().mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT) && !isFocused) {
        isFocused = true;
        handleMouseClick(GLFW_MOUSE_BUTTON_LEFT, bi::mouseInput().getPosition());
    }
    return isFocused;
}

bool GuiWindow::mouseReleased() {
    if (!bi::mouseInput().mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
        isFocused = false;
    }
    return isFocused;
}


void GuiWindow::dragging() {
    glm::vec2 mouse = {bi::mouseInput().toOrthoX(), bi::mouseInput().toOrthoY()};

    if (!isDragging && isFocused) {
        windowMouseDiff = this->position - mouse;
        if (this->isPositionWithinRect(mouse)){
            isDragging = true;
        }
    }

    if (isFocused) {
        this->setPosition(mouse + windowMouseDiff);
    }
}

void GuiWindow::draggingEnd() {

    if (isDragging) {
        this->isDragging = false;
        this->isFocused = false;
    }
}

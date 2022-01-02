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

}

GuiWindow& GuiWindow::setSize(glm::vec2 size) {
    this->size = size;
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

glm::vec2 GuiWindow::positionBottomRight(glm::vec2 size) {
    return {this->position.x + this->size.x - size.x, this->position.y + this->size.y - size.y};
}

glm::vec2 GuiWindow::positionTopRight(glm::vec2 size) {
    return {this->position.x + this->size.x - size.x, this->position.y + size.y};
}

void GuiWindow::draw() {
    ioManager().renderer->drawQuad(this->position, this->size, backgroundColor);
    ioManager().shaperenderer->setLineWidth(this->outlineWidth);
    ioManager().shaperenderer->drawRect(this->position, this->size, outlineColor).endFlushBegin();

    for (auto& child : children){
        child->draw();
    }
}

bool GuiWindow::handleMouseClick(int action, glm::vec2 position) {
    if (isClosed) {
        return false;
    }

    if (action == GLFW_MOUSE_BUTTON_LEFT){
        isFocused = isPositionWithinRect(position);
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

    if (!isFocused) {
        mouseClicked();
    }

    else if (!bi::mouseInput().mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
        isFocused = false;
    }
    return isFocused;
}


void GuiWindow::close() {
    this->isClosed = true;
}

void GuiWindow::show() {
    this->isClosed = false;
}

void GuiWindow::dragging() {

    if (!isFocused) {
        mouseReleased();
    }

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

void GuiWindow::processDragging() {

    if (bi::mouseInput().isDragging) {
        dragging();
    }

    else if (!bi::mouseInput().isDragging) {
        draggingEnd();
    }
}


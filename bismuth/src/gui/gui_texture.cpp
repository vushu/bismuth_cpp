#include "bismuth/iomanager.hpp"
#include <bismuth/gui/gui_texture.hpp>
using namespace bi::gui;

void GuiTexture::init() {
    this->textureId = ioManager().assetmanager->loadTexture(this->filepath);
}

void GuiTexture::setColor(glm::vec4 color) {
    this->color = color;
}

void GuiTexture::draw() {
    ioManager().renderer->drawTexture(this->position, size, color, textureId);
}

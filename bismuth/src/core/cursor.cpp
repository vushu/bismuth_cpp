#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/mouselistener.hpp"
#include <bismuth/cursor.hpp>
using namespace bi;

void Cursor::init(){
    currentTextureId = pointerTextureId = bi::ioManager().assetmanager->loadTexture(pointerFilePath);
    mouseOverTextureId = bi::ioManager().assetmanager->loadTexture(mouseOverFilePath);
}

void Cursor::setColor(glm::vec4 color){
    this->color = color;
}

void Cursor::setMouseOver(bool enable) {
    currentTextureId = pointerTextureId;
    if (enable)
        currentTextureId = mouseOverTextureId;
}

void Cursor::draw() {
    bi::ioManager().renderer->drawTexture(mouseInput().getPosition() + offset, size, color, currentTextureId, 0);
}


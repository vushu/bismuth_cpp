#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/mouselistener.hpp"
#include <bismuth/cursor.hpp>
using namespace bi;

Cursor::~Cursor() {

}

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

void Cursor::setTexture(std::string pointerFilePath, std::string mouseOverFilePath) {
    this->pointerFilePath = pointerFilePath;
    this->mouseOverFilePath = mouseOverFilePath;
    init();
}

void Cursor::draw() {
    if (bi::mouseInput().xPos != -1)
        bi::ioManager().renderer->drawTexture(mouseInput().getPosition() + offset, size, color, currentTextureId, 0);
}


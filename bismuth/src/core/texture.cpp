#include "bismuth/glhelper.hpp"
#include "bismuth/logging.hpp"
#include <GL/gl.h>
#include <bismuth/texture.hpp>

using namespace bi;

Texture::Texture() {}

Texture::~Texture() {}

void Texture::init(std::string filepath) {
     glhelper::TextureInfo textureInfo = glhelper::generateTexture(filepath);
     this->textureId = textureInfo.textureId;
     this->width = textureInfo.width;
     this->height = textureInfo.height;
     bi::log("Successfully loaded " + filepath);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

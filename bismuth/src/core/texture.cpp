#include "bismuth/glhelper.hpp"
#include "bismuth/logging.hpp"
#include <bismuth/texture.hpp>
#include <glad/glad.h>

using namespace bi;

Texture::Texture(std::string filepath) {
    this->filepath = filepath;
}

Texture::~Texture() {
    bi::log("Texture destroyed");
}

void Texture::init() {
     glhelper::TextureInfo textureInfo = glhelper::generateTexture(this->filepath);
     this->textureId = textureInfo.textureId;
     this->width = textureInfo.width;
     this->height = textureInfo.height;
     bi::log("Texture initialized: " + filepath);
     bi::log("Texture Width: " + std::to_string(this->width));
     bi::log("Texture Height: " + std::to_string(this->height));
}

void Texture::bind() {
    //log("TextureID: " + std::to_string(textureId));
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

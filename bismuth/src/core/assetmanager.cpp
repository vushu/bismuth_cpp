#include <bismuth/logging.hpp>
#include <bismuth/texture.hpp>
#include <bismuth/assetmanager.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <bismuth/font.hpp>

using namespace bi;

AssetManager::AssetManager () {}
AssetManager::~AssetManager() {
    bi::log("AssetManager destroyed");
}


void AssetManager::initDefaults() {
    this->defaultFont.loadFnt("resources/assets/fonts/neuropol.fnt");
}

int AssetManager::loadTexture(std::string filepath) {
    int texId = 0;

    if (textureExists(filepath)) {
        return getTexture(filepath).textureId;
    }
    else {
        std::unique_ptr<Texture> texture = std::make_unique<Texture>(filepath);
        texture->init();
        texId = texture->textureId;
        filepaths.emplace(texId, filepath);
        this->values.push_back(texture.get());
        textures.emplace(filepath, std::move(texture));
    }
    return texId;
}

Texture& AssetManager::getTexture(int textureId) {
    if (filepaths.count(textureId) > 0) {
        return getTexture(filepaths.at(textureId));
    }
    throw std::runtime_error("No texture width Id: " + std::to_string(textureId));
}

Texture& AssetManager::getTexture(std::string filepath) {
    if (!textureExists(filepath)){
        loadTexture(filepath);
    }
    return *textures.at(filepath);
}

Font& AssetManager::getFont(std::string filepath) {
    if (fonts.count(filepath) > 0) {
        return *fonts.at(filepath);
    }
    std::unique_ptr<Font> font = std::make_unique<Font>();
    font->loadFnt(filepath);
    this->fonts.emplace(filepath, std::move(font));
    return *this->fonts.at(filepath);
}


Font& AssetManager::getDefaultFont()  {
    return this->defaultFont;
}

bool AssetManager::textureExists(std::string filepath) {
    return textures.count(filepath) > 0;
}

std::vector<Texture*>& AssetManager::getTextures() {
    return values;
}


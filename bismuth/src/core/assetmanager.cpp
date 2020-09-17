#include "bismuth/texture.hpp"
#include <bismuth/assetmanager.hpp>
#include <memory>
#include <stdexcept>

using namespace bi;

AssetManager::AssetManager () {}
AssetManager::~AssetManager() { }

int AssetManager::loadTexture(std::string filepath) {
    int texId = 0;

    if (textureExists(filepath)) {
        return getTexture(filepath).textureId;
    }
    else {
        std::unique_ptr<Texture> texture = std::make_unique<Texture>(filepath);
        texture->init();
        texId = texture->textureId;
        AssetManager::get().textures.emplace(filepath, std::move(texture));
    }
    return texId;
}

Texture& AssetManager::getTexture(std::string filepath) {
    if (AssetManager::get().textures.count(filepath) > 0){
        return *AssetManager::get().textures.at(filepath);
    }
    throw std::runtime_error("Not Texture not found");
}

bool AssetManager::textureExists(std::string filepath) {
    return AssetManager::get().textures.count(filepath) > 0;
}


bi::AssetManager& bi::assetManager() {
    return AssetManager::get();
}

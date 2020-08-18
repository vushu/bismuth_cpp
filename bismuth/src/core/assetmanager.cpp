#include <bismuth/assetmanager.hpp>
#include <stdexcept>

using namespace bi;

AssetManager::AssetManager() { }

AssetManager::~AssetManager() { }

std::string AssetManager::loadTexture(std::string filepath) {
    if (textures.count(filepath) == 0){
        Texture texture = Texture(filepath);
        texture.init();
        textures.emplace(filepath, std::move(texture));
    }
    return filepath;
}

Texture& AssetManager::getTexture(std::string filepath) {
    if (textures.count(filepath) > 0){
        return this->textures.at(filepath);
    }
    throw std::runtime_error("Not Texture not found");
}

bool AssetManager::textureExists(std::string filepath) {
    return this->textures.count(filepath) > 0;
}



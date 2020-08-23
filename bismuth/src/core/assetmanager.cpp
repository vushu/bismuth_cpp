#include <bismuth/assetmanager.hpp>
#include <stdexcept>

using namespace bi;

AssetManager::AssetManager() { }

AssetManager::~AssetManager() { }

int AssetManager::loadTexture(std::string filepath) {
    int texId = 0;
    if (textures.count(filepath) == 0){
        Texture texture = Texture(filepath);
        texture.init();
        texId = texture.textureId;
        textures.emplace(filepath, std::move(texture));
    }
    return texId;
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



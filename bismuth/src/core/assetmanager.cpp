#include <bismuth/texture.hpp>
#include <bismuth/assetmanager.hpp>
#include <memory>
#include <stdexcept>
#include <string>

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
        filepaths.emplace(texId, filepath);
        AssetManager::get().textures.emplace(filepath, std::move(texture));
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
    return *AssetManager::get().textures.at(filepath);
}

bool AssetManager::textureExists(std::string filepath) {
    return AssetManager::get().textures.count(filepath) > 0;
}


bi::AssetManager& bi::assetManager() {
    return AssetManager::get();
}

#include <bismuth/tiledmanager.hpp>
using namespace bi;

TiledManager::TiledManager() { }
TiledManager::~TiledManager() { }

TiledMap& TiledManager::loadTileMap(std::string filepath) {
    if (tiledMaps.count(filepath) > 0)
        return *this->tiledMaps.at(filepath);
    else {
        this->tiledMaps.emplace(filepath, std::make_unique<TiledMap>(filepath));
    }
    return *this->tiledMaps.at(filepath);
}

void TiledManager::draw(std::string filepath, int layerNumber, Renderer& renderer) {
    for(auto& tile : loadTileMap(filepath).getTiles(layerNumber)) {
        renderer.drawTexture(tile.getPosition(), tile.getTileSize(), {1,1,1,1}, tile.getTextureId(), 0, tile.getTexCoords());
    }
}



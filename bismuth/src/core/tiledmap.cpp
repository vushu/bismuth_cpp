#include "bismuth/assetmanager.hpp"
#include <bismuth/tiledmap.hpp>
#include <bismuth/logging.hpp>
#include <tmxlite/TileLayer.hpp>
using namespace bi;

TiledMap::~TiledMap() { }

std::vector<bi::Tile> TiledMap::getTiles(unsigned int layerNumber) {
    return tiles.at(layerNumber);
}

void TiledMap::loadMap() {
    tmx::Map map;
    if (map.load(filePath)) {
        tileSize = { map.getTileSize().x, map.getTileSize().y };
        const auto& ts = map.getTilesets();

        for (int i = 0; i < ts.size(); i++) {
            this->tilesets.emplace(i, ts[i]);
            this->textureIds.emplace(i, bi::assetManager().loadTexture(ts[i].getImagePath()));
        }

        int tilePosX = 0;
        int tilePosY = 0;
        int tileCount = 0;
        int objectCount = 0;
        int tileSetIdx = -1;

        for (const auto& layer : map.getLayers()) {

            if (layer->getType() == tmx::Layer::Type::Tile) {
                std::vector<bi::Tile> tileList;
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();

                for (int i = 0; i < tileLayer.getTiles().size(); i++) {
                    const auto& t = tileLayer.getTiles()[i];

                    tilePosX = i % tileLayer.getSize().x;
                    tilePosY = (int) (i / tileLayer.getSize().x);

                    glm::vec2 pos = {tilePosX * tileSize.x, tilePosY * tileSize.y};

                    tileSetIdx = tilesetIndexOfTile(t.ID);

                    const auto &imgSize = this->tilesets.at(tileSetIdx).getImageSize();

                    bi::Tile tile(t.ID, textureIds.at(tileSetIdx), {imgSize.x, imgSize.y}, pos, {tileSize.x, tileSize.y});

                    tileList.push_back(tile);
                }
                tiles.emplace(tileCount, std::move(tileList));
                tileCount++;
            }
        }

    }
}

int TiledMap::tilesetIndexOfTile(unsigned int tileId) {
    int tilesetIndex = 0;
    for(int i = 0; i < tilesets.size(); i++) {
        if (tilesets.at(i).hasTile(tileId)) {
            tilesetIndex = i;
            break;
        }
    }
    return tilesetIndex;
}



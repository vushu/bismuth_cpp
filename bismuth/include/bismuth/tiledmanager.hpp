#pragma once
#include <vector>
#include <map>
#include <bismuth/tile.hpp>
#include <bismuth/tiledmap.hpp>
#include <bismuth/assetmanager.hpp>
#include <bismuth/renderer.hpp>
#include <tmxlite/Tileset.hpp>
namespace bi {
    class TiledManager {
        public:
            // constructors, asssignment, destructor
            TiledManager();

            ~TiledManager();
            TiledMap& loadTileMap(std::string filepath);
            void draw(std::string filepath, int layerNumber, Renderer& renderer);
        private:
            //layer index, and tiles
            std::map<std::string, std::unique_ptr<TiledMap>> tiledMaps;

    };
}

#pragma once
#include "bismuth/logging.hpp"
#include <vector>
#include <map>
#include <bismuth/tile.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/Map.hpp>

namespace bi {
    class TiledMap{
        public:
            // constructors, asssignment, destructor
            TiledMap(std::string filepath) : filePath(filepath) {
                loadMap();
                //bi::log("loaded map");
            }
            ~TiledMap();

            std::vector<Tile> getTiles(unsigned int layerNumber);
            void loadMap();

        private:

            glm::vec2 tileSize;
            std::string filePath;
            //layers
            std::map<int, std::vector<Tile>> tiles;
            std::map<int, tmx::Tileset> tilesets;
            std::map<int, int> textureIds;
            int tilesetIndexOfTile (unsigned int tileId);

            //tmx::Map map;
    };
}

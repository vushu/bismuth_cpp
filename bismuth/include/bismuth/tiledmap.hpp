#pragma once
#include "bismuth/logging.hpp"
#include <vector>
#include <map>
#include <bismuth/tile.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Object.hpp>

namespace bi {
    struct TiledObject {
        tmx::Object object;
        Tile tile;
        glm::vec2 position;
    };
    class TiledMap{
        public:
            TiledMap(std::string filepath) : filePath(filepath) {
                loadMap();
            }

            ~TiledMap();

            std::vector<Tile>& getTiles(unsigned int layerNumber);
            std::vector<TiledObject>& getObjects(unsigned int objectNumber);
            void loadMap();

        private:

            glm::vec2 tileSize;
            std::string filePath;
            //layers
            std::map<int, std::vector<Tile>> tiles;
            std::map<int, tmx::Tileset> tilesets;
            std::map<int, int> textureIds;
            std::map<int, std::vector<TiledObject>> objects;
            int tilesetIndexOfTile (unsigned int tileId);
    };
}

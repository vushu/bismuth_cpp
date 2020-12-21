#pragma once
#include "bismuth/logging.hpp"
#include <bismuth/tile.hpp>
#include <map>
#include <string>
#include <tmxlite/Map.hpp>
#include <tmxlite/Object.hpp>
#include <tmxlite/Tileset.hpp>
#include <vector>

namespace bi {
class TiledObject {

private:
    std::map<std::string, std::string> metadata;
    void addMetaData(std::string key, std::string value)
    {
        this->metadata.emplace(key, value);
    }

public:
    tmx::Object object;
    Tile tile;
    TiledObject(tmx::Object object, Tile tile)
        : object(object)
        , tile(tile)
    {
        for (auto& prop : object.getProperties()) {
            addMetaData(prop.getName(), prop.getStringValue());
            bi::log("added meta: " + prop.getName(), prop.getStringValue());
        }
    }

    bool setMetaData(std::string key, std::string value)
    {
        if (this->metadata.count(key) > 0) {
            this->metadata.emplace(key, value);
            bi::log("Setting metadata");
            return true;
        }
        return false;
    }

    std::string getMetaData(std::string key)
    {
        if (metadata.count(key) > 0) {
            bi::log("getting value metadata");
            return this->metadata.at(key);
        } else {
            bi::log("FaILED GETTING value metadata");
        }
        return "";
    }
};
class TiledMap {
public:
    TiledMap(std::string filepath)
        : filePath(filepath)
    {
        loadMap();
    }

    ~TiledMap();

    std::vector<Tile>& getTiles(unsigned int layerNumber);
    std::vector<TiledObject>& getObjects(unsigned int objectNumber);
    void loadMap();

    glm::vec2 tileCount;
    glm::vec2 tileSize;

private:
    std::string filePath;
    //layers
    std::map<int, std::vector<Tile>> tiles;
    std::map<int, tmx::Tileset> tilesets;
    std::map<int, int> textureIds;
    std::map<int, std::vector<TiledObject>> objects;
    int tilesetIndexOfTile(unsigned int tileId);
};
}

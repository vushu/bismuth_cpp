#pragma once
#include <bismuth/tile.hpp>
#include <vector>
namespace bi {
    class TiledManager {
        public:
            // constructors, asssignment, destructor
            TiledManager();
            ~TiledManager();



        private:
            std::map<int, std::vector<Tile>> tiles;
    };
}

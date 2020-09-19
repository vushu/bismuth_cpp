#pragma once
#include "bismuth/renderer.hpp"
#include "bismuth/tiledmap.hpp"
#include "bismuth/tile.hpp"
#include <vector>
class ObjectSystem {
    public:
        // constructors, asssignment, destructor
        ObjectSystem ();
        ~ObjectSystem ();
        static void update(std::vector<bi::TiledObject>& objects, bi::Renderer& renderer);

    private:

};

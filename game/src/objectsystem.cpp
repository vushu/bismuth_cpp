#include "objectsystem.hpp"
#include "bismuth/renderer.hpp"
#include "bismuth/tile.hpp"

ObjectSystem::ObjectSystem() {}
ObjectSystem::~ObjectSystem() {}

void ObjectSystem::update(std::vector<bi::TiledObject> &objects, bi::Renderer& renderer) {
    for (bi::TiledObject& o : objects) {
        if (o.object.getName() == "player") {
            o.tile.setPosition({101, 200});
        }
        renderer.drawTile(o.tile, {1,1,1,1});
    }
}

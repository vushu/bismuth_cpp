#pragma once
#include <entt/entt.hpp>
#include "components.hpp"
#include <bismuth/bismuth.hpp>

namespace RectRenderSystem {
    void update(entt::registry& registry, bi::ShapeRenderer& shapeRenderer, float angle) {
        registry.view<Position, Size>().each([&](Position& pos, Size& size){
                shapeRenderer.drawRect({pos.x, pos.y}, {size.x, size.y}, {0,1,0,1}, angle, true);

                });

        shapeRenderer.flush();
    }
}

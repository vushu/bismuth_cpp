#pragma once
#include <bismuth/renderer.hpp>
#include <entt/entt.hpp>
#include <box2d/box2d.h>
class RenderSystem {
    public:
        // constructors, asssignment, destructor
        RenderSystem ();
        ~RenderSystem ();

        void update(bi::Renderer& renderer,float dt, b2World& world, entt::registry& registry);

    private:

};

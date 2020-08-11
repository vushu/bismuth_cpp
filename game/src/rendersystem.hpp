#pragma once
#include <bismuth/renderer.hpp>
#include <entt/entt.hpp>
class RenderSystem {
    public:
        // constructors, asssignment, destructor
        RenderSystem ();
        ~RenderSystem ();

        void update(bi::Renderer& renderer,float dt, entt::registry& registry);

    private:

};

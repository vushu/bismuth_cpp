#pragma once
#include <bismuth/renderbatch.hpp>
#include <bismuth/sprite.hpp>
#include <entt/entt.hpp>
namespace bi {
    class RenderingSystem {
        public:
            // constructors, asssignment, destructor
            RenderingSystem ();
            ~RenderingSystem ();
            void addSprite(Sprite sprite);
            void update(float dt, entt::registry& registry);

        private:
            std::vector<RenderBatch> renderbatches;

    };
}

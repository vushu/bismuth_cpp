#pragma once
#include <entt/entt.hpp>
namespace bi {
    class RenderingSystem {
        public:
            // constructors, asssignment, destructor
            RenderingSystem ();
            ~RenderingSystem ();
            void update(float dt, entt::registry& registry);

        private:

    };
}

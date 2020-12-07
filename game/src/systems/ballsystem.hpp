#pragma once
#include "playerball.hpp"
#include <entt/entt.hpp>
class BallSystem {
    public:
        // constructors, asssignment, destructor
        BallSystem();
        ~BallSystem();
        void update(PlayerBall &playerball, entt::registry &registry);

    private:
};

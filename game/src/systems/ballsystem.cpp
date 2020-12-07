#include "ballsystem.hpp"
#include "../components/components.hpp"
#include "playerball.hpp"
#include <glm/glm.hpp>

void BallSystem::update(PlayerBall& playerball, entt::registry &registry) {
    auto view = registry.view<Ball>();
    for (auto& e : view){
        Ball& b = view.get<Ball>(e);
        playerball.mAngle = b.angle;
        playerball.mPosition = {b.posX, b.posY};
        playerball.mSize = {b.sizeX, b.sizeY};
    }

}


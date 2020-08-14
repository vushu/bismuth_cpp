#include "rendersystem.hpp"
#include "components.hpp"

RenderSystem::RenderSystem() { }
RenderSystem::~RenderSystem() { }

void RenderSystem::update(bi::Renderer& renderer, float dt, entt::registry& registry) {

    auto view = registry.view<Player, Movement>();

    for (auto entity : view ) {
        auto& player = view.get<Player>(entity);
        auto& movement = view.get<Movement>(entity);

        auto& spr = renderer.getSprite(player.batchId, player.spriteId);
        //if (spr.position.x != movement.x) {
        spr.setPosition(spr.position + glm::vec2(movement.x * dt * 10, movement.y * dt * 10 ));


    }
}

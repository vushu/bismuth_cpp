#include "rendersystem.hpp"
#include "components.hpp"

RenderSystem::RenderSystem() { }
RenderSystem::~RenderSystem() { }

void RenderSystem::update(bi::Renderer& renderer, float dt, b2Body* body, entt::registry& registry) {
    const float M2P=60;
    const float P2M=1/M2P;

    auto view = registry.view<Player, Movement>();

    for (auto entity : view ) {
        auto& player = view.get<Player>(entity);
        auto& movement = view.get<Movement>(entity);

        auto& spr = renderer.getSprite(player.batchId, player.spriteId);
        spr.setPosition(glm::vec2(body->GetPosition().x * M2P, body->GetPosition().y * M2P));
        //if (spr.position.x != movement.x) {
        //spr.setPosition(spr.position + glm::vec2(movement.x * dt * 10, movement.y * dt * -10 ));


    }
    }

#include "rendersystem.hpp"
#include <bismuth/logging.hpp>
#include <bismuth/physicsmanager.hpp>
#include "components.hpp"
#include <glm/gtx/string_cast.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/glm.hpp>

RenderSystem::RenderSystem() { }
RenderSystem::~RenderSystem() { }

void RenderSystem::update(bi::Renderer& renderer, float dt, b2World& world, entt::registry& registry) {
    //const float M2P=32;
    //const float P2M=1/M2P;
    //float maxTime = 0.0f;

    //auto view = registry.view<Block, Movement>();

    //for (auto entity : view ) {
    //auto& player = view.get<Player>(entity);
    //auto& movement = view.get<Movement>(entity);

    //auto& spr = renderer.getSprite(player.batchId, player.spriteId);


    for (b2Body* b = world.GetBodyList(); b; b=b->GetNext()){
        if (b->GetUserData() != NULL) {
            bi::SpriteRenderer* spr = (bi::SpriteRenderer*) b->GetUserData();
            spr->setPosition(glm::vec2((b->GetPosition().x  - spr->scale.x * 0.5f * bi::P2M) * bi::M2P,  (b->GetPosition().y - spr->scale.y * 0.5f * bi::P2M) * bi::M2P));
            spr->setRotation(b->GetAngle());
        }
    }
    //spr.setRotation(spr.angleDegrees + dt * 10.0f);
    //if (spr.position.x != movement.x) {
    //spr.setPosition(spr.position + glm::vec2(movement.x * dt * 10, movement.y * dt * -10 ));


    //}
}

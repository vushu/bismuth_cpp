#include "rendersystem.hpp"
#include <bismuth/logging.hpp>
#include <bismuth/physicsmanager.hpp>
#include "components.hpp"
#include <glm/gtx/string_cast.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/glm.hpp>
#include "shapebuilder.hpp"
#include <entt/entt.hpp>

RenderSystem::RenderSystem() { }
RenderSystem::~RenderSystem() { }

void RenderSystem::update(bi::ShapeRenderer &shaperenderer, bi::Renderer& renderer, float dt,
        b2World &world, entt::registry &registry, int texId) {
    // const float M2P=32;
    // const float P2M=1/M2P;
    // float maxTime = 0.0f;

    // auto view = registry.view<Block, Movement>();

    // for (auto entity : view ) {
    // auto& player = view.get<Player>(entity);
    // auto& movement = view.get<Movement>(entity);

    // auto& spr = renderer.getSprite(player.batchId, player.spriteId);

    bool hasbody = false;

    if (world.GetBodyCount() > 0) {
        renderer.beginBatch();
    }
    for (b2Body *b = world.GetBodyList(); b; b = b->GetNext()) {
        bi::log("has body");
        /*
           if (b->GetUserData() != NULL) {
           bi::SpriteRenderer* spr = (bi::SpriteRenderer*) b->GetUserData();
           spr->setPosition(glm::vec2((b->GetPosition().x  - spr->scale.x * 0.5f *
           bi::P2M) * bi::M2P,  (b->GetPosition().y - spr->scale.y * 0.5f * bi::P2M)
         * bi::M2P)); spr->setRotation(b->GetAngle());
         }
         */
        if (b->GetUserData() != NULL) {

            shaperenderer.drawPolygon(
                    {b->GetPosition().x * bi::M2P, b->GetPosition().y * bi::M2P},
                    b->GetFixtureList()[0].GetShape()->m_radius * bi::M2P, 16,
                    {0, 1, 0, 1}, b->GetAngle(), true);

            float rad = b->GetFixtureList()[0].GetShape()->m_radius;
            float sx = b->GetFixtureList()[0].GetShape()->m_radius * bi::M2P * 2;
            float sy = sx;

            renderer.drawTexture((glm::vec2(b->GetPosition().x, b->GetPosition().y) - glm::vec2(rad, rad)) * bi::M2P, {sx, sy}, {1,1,1,1}, texId, b->GetAngle());





        }

        // spr->setPosition(glm::vec2((b->GetPosition().x  - spr->scale.x * 0.5f *
        // bi::P2M) * bi::M2P,  (b->GetPosition().y - spr->scale.y * 0.5f * bi::P2M)
        // * bi::M2P)); spr->setRotation(b->GetAngle());
        hasbody = true;
    }
    // spr.setRotation(spr.angleDegrees + dt * 10.0f);
    if (hasbody) {

        renderer.endBatch();
        renderer.flush();
        shaperenderer.flush();
    }
    // if (spr.position.x != movement.x) {
    // spr.setPosition(spr.position + glm::vec2(movement.x * dt * 10, movement.y *
    // dt * -10 ));

    //}
}

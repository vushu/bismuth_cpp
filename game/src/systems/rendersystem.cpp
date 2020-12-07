#include "rendersystem.hpp"
#include <bismuth/logging.hpp>
#include <bismuth/physicsmanager.hpp>
#include "../components/components.hpp"
#include <glm/gtx/string_cast.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include "playerball.hpp"
#include "../builders/shapebuilder.hpp"
#include <entt/entt.hpp>

RenderSystem::RenderSystem() { }
RenderSystem::~RenderSystem() { }

void RenderSystem::update(bi::ShapeRenderer &shaperenderer, bi::Renderer& renderer, float dt,
        b2World &world, entt::registry& registry) {

    bool hasbody = false;

    if (world.GetBodyCount() > 0) {
        renderer.resetStats();
        //renderer.beginBatch();
    }
    for (b2Body *b = world.GetBodyList(); b; b = b->GetNext()) {

        /*
           if (b->GetUserData() != NULL) {
           bi::SpriteRenderer* spr = (bi::SpriteRenderer*) b->GetUserData();
           spr->setPosition(glm::vec2((b->GetPosition().x  - spr->scale.x * 0.5f *
           bi::P2M) * bi::M2P,  (b->GetPosition().y - spr->scale.y * 0.5f * bi::P2M)
         * bi::M2P)); spr->setRotation(b->GetAngle());
         }
         */
        float rad = b->GetFixtureList()[0].GetShape()->m_radius;
        //float rad = 100.0f;
        float sx = b->GetFixtureList()[0].GetShape()->m_radius * bi::M2P * 2;
        float sy = sx;

        if (b->GetPosition().y * bi::M2P > 1000) {
            //bi::log("body destroyed");
            world.DestroyBody(b);
            continue;
        }

        if (b->GetUserData() != NULL) {
            bi::Texture* texture = (bi::Texture*) b->GetUserData();
            renderer.drawTexture((glm::vec2(b->GetPosition().x, b->GetPosition().y) - glm::vec2(rad, rad)) * bi::M2P, {sx, sy}, {1,0,0,1}, texture->textureId, b->GetAngle());
        }

        shaperenderer.drawPolygon(
                {b->GetPosition().x * bi::M2P, b->GetPosition().y * bi::M2P},
                b->GetFixtureList()[0].GetShape()->m_radius * bi::M2P, 24,
                {0, 1, 0, 1}, b->GetAngle(), false);

        //PlayerBall* playerball = (PlayerBall*) b->GetUserData();
        //playerball->mAngle = b->GetAngle();
        //playerball->mPosition = (glm::vec2(b->GetPosition().x, b->GetPosition().y) - glm::vec2(rad, rad)) * bi::M2P;
        //bi::log("OK");

        hasbody = true;
    }

    if (hasbody) {

        //renderer.endBatch();
        renderer.endFlushBegin();
        shaperenderer.flush();
        //bi::log("Flushing");
    }
}


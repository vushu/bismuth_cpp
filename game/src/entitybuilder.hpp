#pragma once
#include <box2d/b2_world.h>
#include <bismuth/renderer.hpp>
#include <entt/entt.hpp>
class EntityBuilder{
    public:
        // constructors, asssignment, destructor
        EntityBuilder();
        ~EntityBuilder();

        EntityBuilder& sprite(std::string filepath);
        EntityBuilder& setColor(glm::vec4 color);
        EntityBuilder& at(float x, float y);
        EntityBuilder& size(float x, float y);
        EntityBuilder& vel(float x, float y);
        void buildPlayer(bi::Renderer& renderer, entt::registry& registry);
        void buildEnemy(bi::Renderer& renderer, b2World& world, entt::registry& registry, bool isStatic, bool isBox = true);
        void buildBox(b2World& world, bi::Renderer& renderer, bool isStatic, bool isBox);

    private:
        std::shared_ptr<bi::SpriteRenderer> spr;
        bi::RenId rid;
        glm::vec2 position{0,0};
        glm::vec2 scale{32,32};
        glm::vec4 color{1,1,1,1};
        glm::vec2 velocity{1,1};

        std::unique_ptr<bi::Sprite> msprite;
        void reset();

};

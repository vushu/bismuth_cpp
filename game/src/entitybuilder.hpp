#pragma once
#include <bismuth/renderer.hpp>
#include <entt/entt.hpp>
class EntityBuilder{
    public:
        // constructors, asssignment, destructor
        EntityBuilder();
        ~EntityBuilder();

        EntityBuilder& sprite(std::string filepath);
        EntityBuilder& color(glm::vec4 color);
        EntityBuilder& at(float x, float y);
        EntityBuilder& size(float x, float y);
        EntityBuilder& vel(float x, float y);
        void buildPlayer(bi::Renderer& renderer, entt::registry& registry);

    private:
        std::shared_ptr<bi::SpriteRenderer> spr;
        bi::RenId rid;
        glm::vec2 position{0,0};
        glm::vec2 scale{32,32};
        glm::vec2 velocity{1,1};
};

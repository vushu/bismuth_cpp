#pragma once
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include <entt/entt.hpp>
#include <bismuth/assetmanager.hpp>
class ShapeBuilder{
    public:
        // constructors, asssignment, destructor
        ShapeBuilder();

        ~ShapeBuilder();

        ShapeBuilder& setRadius(float radius);
        ShapeBuilder& setPosition(float x, float y);
        ShapeBuilder& setTexture(bi::Texture* texture);
        ShapeBuilder& isStatic(bool enable);
        ShapeBuilder& setUserData(void* userData);
        void buildBall(b2World& world, entt::registry& registry);

    private:
        bool staticObject = false;
        float radius = 0.0f;
        glm::vec2 position{0,0};
        glm::vec2 size{32,32};
        glm::vec4 color{1,1,1,1};
        glm::vec2 velocity{1,1};
        void* userData;
        //int textureId = 0;
        bi::Texture* texture;
        void reset();



};

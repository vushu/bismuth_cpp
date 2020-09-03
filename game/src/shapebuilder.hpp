#pragma once
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include <entt/entt.hpp>
class ShapeBuilder{
    public:
        // constructors, asssignment, destructor
        ShapeBuilder();

        ~ShapeBuilder();

        ShapeBuilder& setRadius(float radius);
        ShapeBuilder& setPosition(float x, float y);
        ShapeBuilder& setTexture(int texId);
        ShapeBuilder& isStatic(bool enable);
        void buildBall(b2World& world, entt::registry& registry);

    private:
        bool staticObject = false;
        float radius = 0.0f;
        glm::vec2 position{0,0};
        glm::vec2 size{32,32};
        glm::vec4 color{1,1,1,1};
        glm::vec2 velocity{1,1};
        int textureId = 0;
        void reset();



};

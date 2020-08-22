#pragma once
#include <bismuth/application.hpp>
#include <entt/entt.hpp>
#include <bismuth/spriterenderer.hpp>
#include "rendersystem.hpp"
#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <memory>

class MyGame : public bi::Application {
    public:
        // constructors, asssignment, destructor
        MyGame() : bi::Application(1024, 768, "MyGAME") {}
        ~MyGame();

    protected:
        void update(float dt) override;
        void init() override;
        entt::registry registry;
        RenderSystem renderSystem;
        std::shared_ptr<bi::Sound> s1;
        std::shared_ptr<bi::Sound> s2;
        std::shared_ptr<bi::Sound> s3;
        std::shared_ptr<bi::Sound> s4;
    private:
        glm::vec2 position;

        int ticks = 0;
        std::unique_ptr<bi::SpriteRenderer> spriterenderer;

        b2BodyDef groundBodyDef;
        b2Vec2 gravity{0.0f, 10.0f};
        b2World world{gravity};
        //b2BodyDef boxBodyDef;
        b2Body* boxBody;


};

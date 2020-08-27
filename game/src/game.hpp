#pragma once
#include "bismuth/shaperenderer.hpp"
#include "glm/fwd.hpp"
#include <array>
#include <bismuth/application.hpp>
#include <entt/entt.hpp>
#include <bismuth/spriterenderer.hpp>
//#include "rndersystem.hpp"
#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <bismuth/font.hpp>
#include <bismuth/assetmanager.hpp>
#include <memory>

class MyGame : public bi::Application {
    public:
        // constructors, asssignment, destructor
        MyGame() : bi::Application(1024, 768, "MyGAME") {}
        //MyGame() : bi::Application(800, 600, "MyGAME") {}
        ~MyGame();

    protected:
        void update(float dt) override;
        void init() override;
        entt::registry registry;
        //RenderSystem renderSystem;
        std::shared_ptr<bi::Sound> s1;
        std::shared_ptr<bi::Sound> s2;
        std::shared_ptr<bi::Sound> s3;
        std::shared_ptr<bi::Sound> s4;
    private:
        glm::vec2 position, size;

        std::unique_ptr<bi::SpriteRenderer> spriterenderer;

        float mAngle = 0;
        float camX = 0;
        float camY = 0;
        int textureId = -1;
        b2BodyDef groundBodyDef;
        b2Vec2 gravity{0.0f, 10.0f};
        b2World world{gravity};
        glm::vec4 color;
        glm::vec4 textColor {0,0,0,1};
        std::array<char, 256> text;
        std::unique_ptr<bi::ShapeRenderer> shaperenderer;
        void drawStuff(float dt);
        void drawStuff2(float dt);


        //b2BodyDef boxBodyDef;
        b2Body* boxBody;
        std::unique_ptr<bi::Font> font;

};

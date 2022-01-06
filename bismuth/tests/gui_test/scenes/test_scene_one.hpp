#pragma once
#include "bismuth/gui/guilabel.hpp"
#include "bismuth/scene.hpp"
class TestSceneOne : public bi::Scene {
    public:
        TestSceneOne();
        ~TestSceneOne();

        void init() override;
        void start() override;
        void processInput(float dt) override;
        void update(float dt) override;
        void render(float dt) override;
        void close() override;
    private:
        std::unique_ptr<bi::gui::GuiLabel> titleLabel;
};

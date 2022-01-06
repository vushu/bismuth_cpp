#pragma once
#include "bismuth/scene.hpp"
class TestSceneTwo : public bi::Scene {
    public:
        TestSceneTwo();
        ~TestSceneTwo();

        void init() override;
        void start() override;
        void processInput(float dt) override;
        void update(float dt) override;
        void render(float dt) override;
        void close() override;
    private:
};

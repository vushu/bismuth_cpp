#pragma once
#include "bismuth/bismuth.hpp"
class GuiWindowScene : public bi::Scene {
    public:
        GuiWindowScene();
        ~GuiWindowScene();

        void init() override;
        void start() override;
        void processInput(float dt) override;
        void update(float dt) override;
        void render(float dt) override;
        void close() override;
    private:
        void setupGuiEvents();
        std::unique_ptr<bi::gui::GuiWindow> window;
        std::shared_ptr<bi::gui::GuiLabel> fpsLabel;
        std::shared_ptr<bi::gui::GuiButton> startBtn;
        std::shared_ptr<bi::gui::GuiTexture> guiTexture;
        std::string bismuthSoundFile;
        std::string plingSoundFile;
        std::string explosionSoundFile;
        bi::utils::Counter counter{10, 1.0f};
};

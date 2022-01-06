#pragma once
#include "bismuth/gui/guibutton.hpp"
#include "bismuth/gui/guiwindow.hpp"
#include "bismuth/sound.hpp"
#include "bismuth/texture.hpp"
#include "scenes/test_scene_one.hpp"
#include "scenes/test_scene_two.hpp"
#include <bismuth/bismuth.hpp>
#include <bismuth/utils/counter.hpp>
class GuiTest : public bi::Application{
    public:
        // constructors, asssignment, destructor
        GuiTest() : bi::Application(1024, 768, "bismuth") {
        }
        ~GuiTest();
    private:
        void setupGuiEvents();
        std::unique_ptr<TestSceneOne> testSceneOne;
        std::unique_ptr<TestSceneTwo> testSceneTwo;
    protected:
        void init() override;
        void update(float dt) override;
        void render(float dt) override;
        void processInput(float dt) override;
        std::shared_ptr<bi::gui::GuiLabel> fpsLabel;
        std::unique_ptr<bi::gui::GuiWindow> window;
        std::shared_ptr<bi::gui::GuiButton> startBtn;
        std::string bismuthSoundFile;
        std::string plingSoundFile;
        std::string explosionSoundFile;
        bi::utils::Counter counter{10, 1.0f};
        int soundId;
};

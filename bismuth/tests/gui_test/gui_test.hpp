#pragma once
#include "bismuth/gui/guibutton.hpp"
#include "bismuth/gui/guiwindow.hpp"
#include "bismuth/sound.hpp"
#include "bismuth/texture.hpp"
#include <bismuth/bismuth.hpp>
#include <bismuth/utils/counter.hpp>
class GuiTest : public bi::Application{
    public:
        // constructors, asssignment, destructor
        GuiTest() : bi::Application(1024, 768,"bismuth") {
        }
        ~GuiTest(){};
    protected:
        void init() override;
        void update(float dt) override;
        void render(float dt) override;
        void processInput(float dt) override;
        bi::gui::GuiLabel fpsLabel;
        bi::gui::GuiWindow window;
        //bi::gui::GuiLabel titleLbl;
        bi::gui::GuiButton startBtn;
        //bi::gui::GuiLabel startBtnLbl;
        float accDt = 0;
        //int counter = 10;
        std::string bismuthSoundFile;
        std::string plingSoundFile;
        bi::utils::Counter counter{10, 1.0f};
        int soundId;
};

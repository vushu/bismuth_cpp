#pragma once
#include "bismuth/color.hpp"
#include "bismuth/gui/guielement.hpp"
#include "bismuth/gui/guilabel.hpp"
#include "bismuth/mouse.hpp"
#include "bismuth/gui/gui_callbacks.hpp"
namespace bi {
    namespace gui{
        class GuiButton : public GuiElement{
            public:
                GuiButton() {
                    currentName = "GuiButton";
                    guiLabel = std::make_shared<GuiLabel>();
                }

                void draw() override;
                bool handleMouseClick(int action, glm::vec2 position) override;
                glm::vec4 outlineColor = color::CORNFLOWER_BLUE;
                glm::vec4 backgroundColor = color::fromRGB({44, 0, 138, 1});
                bool isPressed = false;
                GuiButton& setBackgroundColor(glm::vec4 color);
                GuiButton& setSize(glm::vec2 size);
                GuiButton& addLabel(std::shared_ptr<GuiElement> guiLabel);
                GuiButton& setFont(Font* font);
                GuiButton& setText(std::string);
                GuiButton& setTextColor(glm::vec4 color);
                bool isClicked = false;
                bool mouseClicked();
                bool mouseReleased();
                void onLeftClick(GuiButtonCallback callback);
                void onMouseOver(GuiButtonCallback callback);
                void onLeftClickReleased(GuiButtonCallback callback);

                float outlineThickness = 2.0f;
                void processInput() override;

            private:
                bool isMouseOver = false;
                void handleMouseOver();
                void handleMouseLeftClick();
                void handleMouseLeftReleased();
                GuiButtonCallback leftClickCallback;
                GuiButtonCallback leftClickReleasedCallback;
                GuiButtonCallback mouseOverCallback;
                std::shared_ptr<GuiLabel> guiLabel;
                Font* font;
                glm::vec4 lastOutlineColor;
                glm::vec4 lastBackgroundColor;


        };
    }
}

#pragma once
#include "bismuth/color.hpp"
#include "bismuth/gui/guielement.hpp"
#include "bismuth/gui/guilabel.hpp"
namespace bi {
    namespace gui{
        class GuiButton : public GuiElement{
            public:
                // constructors, assignment, destructor
                GuiButton();
                ~GuiButton();

                void draw() override;
                bool handleMouseClick(int action, glm::vec2 position) override;
                glm::vec4 outlineColor = color::CORNFLOWER_BLUE;
                glm::vec4 backgroundColor = color::fromRGB({44, 0, 138, 1});
                bool isPressed = false;
                GuiButton& setBackgroundColor(glm::vec4 color);
                GuiButton& setSize(glm::vec2 size);
                GuiButton& addLabel(GuiElement* guiLabel);
                GuiButton& setFont(Font* font);
                GuiButton& setText(std::string);
                GuiButton& setTextColor(glm::vec4 color);
                bool isClicked = false;
                bool mouseClicked();
                bool mouseReleased();
                float outlineThickness = 2.0f;

            private:
                GuiLabel guiLabel;
                Font* font;

        };
    }
}

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
                glm::vec4 outlineColor = color::SOFT_BLUE;
                glm::vec4 backgroundColor = color::WHITE;
                bool isPressed = false;
                GuiButton& setBackgroundColor(glm::vec4 color);
                GuiButton& setPosition(glm::vec2 position);
                GuiButton& setSize(glm::vec2 size);
                GuiButton& addLabel(GuiLabel* guiLabel);

            private:
                GuiLabel* guiLabel;

        };
    }
}

#pragma once
#include "bismuth/font.hpp"
#include "bismuth/gui/guielement.hpp"
#include "bismuth/color.hpp"
namespace bi {
    namespace gui{

        class GuiLabel : public GuiElement{
            public:
                GuiLabel() {
                    currentName = "GuiLabel";
                };

                void setText(std::string);
                void setText(Font* font,std::string);
                void setColor(glm::vec4 color);
                void setFont(Font* font);
                void draw() override;
                bool handleMouseClick(int action, glm::vec2 position) override;
                bool isClicked = false;
                float fontScale = 0.5f;
            private:
                glm::vec4 color = color::BLACK;
                Font* font;
                std::string text = "";
        };
    }
}

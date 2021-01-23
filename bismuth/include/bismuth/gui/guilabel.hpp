#pragma once
#include "bismuth/font.hpp"
#include "bismuth/gui/guielement.hpp"
namespace bi {
    namespace gui{

        class GuiLabel : public GuiElement{
            public:
                GuiLabel();
                ~GuiLabel();

                void setText(Font* f, std::string);
                void draw() override;
                void handleMouseClick(int action, glm::vec2 position) override;
                bool isClicked = false;
                float fontScale = 0.2f;
                glm::vec4 color;
            private:;
                Font* font;
                std::string text;
        };
    }
}

#include "bismuth/color.hpp"
#include <bismuth/gui/guielement.hpp>
namespace bi{
    class GuiWindow : public GuiElement {

        public:
            // constructors, assignment, destructor
            GuiWindow();

            void draw() override;
            void handleMouseClick(int action, glm::vec2 position) override;
            GuiWindow& setOutlineWidth(float outlineWidth);
            GuiWindow& setBackgroundColor(glm::vec4 color);
            GuiWindow& setOutlineColor(glm::vec4 color);
            GuiWindow& setPosition(glm::vec2 position);
            GuiWindow& setSize(glm::vec2 size);

        private:
            glm::vec2 position {0,0};
            glm::vec2 size {200,200};
            float outlineWidth = 4.0f;
            glm::vec4 outlineColor = color::SOFT_BLUE;
            glm::vec4 backgroundColor = color::WHITE;
    };
}

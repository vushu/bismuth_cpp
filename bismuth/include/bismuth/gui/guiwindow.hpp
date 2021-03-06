#pragma once
#include "bismuth/color.hpp"
#include "bismuth/gui/guibutton.hpp"
#include "glm/fwd.hpp"
#include <bismuth/gui/guielement.hpp>
namespace bi{
    namespace gui {
        class GuiWindow : public GuiElement {

            public:
                // constructors, assignment, destructor
                GuiWindow();

                void draw() override;
                bool handleMouseClick(int action, glm::vec2 position) override;
                GuiWindow& setOutlineWidth(float outlineWidth);
                GuiWindow& setBackgroundColor(glm::vec4 color);
                GuiWindow& setOutlineColor(glm::vec4 color);
                GuiWindow& setPosition(glm::vec2 position);
                GuiWindow& setSize(glm::vec2 size);
                GuiWindow& activateCloseButton();
                GuiWindow& add(GuiElement* guielement);
                GuiWindow& activateCloseButton(bool activate);
                bool mouseClicked();
                bool mouseReleased();
                void dragging();
                void draggingEnd();
                void handleDragging();
                void close();
                void show();

                Font font;
                float outlineWidth = 4.0f;
                glm::vec4 outlineColor = color::SOFT_BLUE;
                glm::vec4 backgroundColor = color::WHITE;
                bool isCloseButtonActivated = false;
                bool isClosed = false;
                GuiButton closeButton;
                GuiLabel closeLabel;
                bool isFocused = false;
                bool isDragging = false;
                bool closeButtonActivated = false;
            private:
                glm::vec2 windowMouseDiff;
                glm::vec2 positionBottomRight(glm::vec2 size);
                glm::vec2 positionTopRight(glm::vec2 size);
        };
    }
}

#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "bismuth/gui/guistyle.hpp"
namespace bi {
    namespace gui {
        class GuiElement{
            public:
                virtual ~GuiElement() {
                    for(auto& element : children){
                        delete element;
                    }
                }

                GuiElement& getParent() {
                    return *parent;
                }

                virtual void draw() = 0;
                virtual void handleMouseClick(int action, glm::vec2 position) = 0;

                glm::vec2 position, size;
                unsigned int placement = TOP_LEFT;
                GuiElement* parent = nullptr;

            protected:
                std::vector<GuiElement*> children;

        };
    }
}

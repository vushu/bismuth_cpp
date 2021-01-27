#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "bismuth/collision/collision.hpp"
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
                virtual bool handleMouseClick(int action, glm::vec2 position) = 0;

                void setPosition(glm::vec2 position) {
                    this->position = position;
                    for (auto& child : children) {
                        child->position = this->position + child->offset;
                    }
                }

                bool isPositionWithinRect(glm::vec2 position){
                    return bi::collision::isPositionWithinRect(position, this->position,  this->size);
                }

                glm::vec2 position, size, offset;
                unsigned int placement = TOP_LEFT;
                GuiElement* parent = nullptr;

            protected:
                std::vector<GuiElement*> children;

        };
    }
}

#pragma once
#include <glm/glm.hpp>
#include <vector>
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
        GuiElement* parent = nullptr;
    protected:
        std::vector<GuiElement*> children;

};

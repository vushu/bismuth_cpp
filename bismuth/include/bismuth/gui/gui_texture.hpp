#pragma once
#include "gui_element.hpp"
namespace bi{
    namespace gui{
        class GuiTexture : GuiElement {
            public:
                GuiTexture(std::string filepath) : filepath(filepath) {}
                void init();
                void draw() override;
                void setColor(glm::vec4 color);
            private:
                glm::vec4 color;
                std::string filepath;
                int textureId;
        };
    }
}

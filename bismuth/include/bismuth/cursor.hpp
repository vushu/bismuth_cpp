#pragma once
#include <string>
#include <glm/glm.hpp>
#include <bismuth/color.hpp>
namespace bi{
    class Cursor{
        public:
            // constructors, assignment, destructor
            Cursor(std::string pointerFilePath, std::string mouseOverFilePath) : pointerFilePath(pointerFilePath), mouseOverFilePath(mouseOverFilePath)  {};
            ~Cursor();
            void init();
            void draw();
            void setMouseOver(bool enable);
            void setColor(glm::vec4 color);
            void setTexture(std::string pointerFilePath, std::string mouseOverFilePath);
            glm::vec2 size {20, 20};
            glm::vec2 offset {-4,-2};
        private:
            std::string pointerFilePath, mouseOverFilePath;
            int pointerTextureId;
            int currentTextureId;
            int mouseOverTextureId;
            glm::vec4 color = color::WHITE;

    };
}

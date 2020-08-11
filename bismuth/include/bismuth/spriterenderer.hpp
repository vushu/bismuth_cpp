#pragma once
#include <bismuth/sprite.hpp>
#include <glm/glm.hpp>
namespace bi  {
    class SpriteRenderer
    {
        public:
            SpriteRenderer(std::unique_ptr<Sprite> sprite);
            ~SpriteRenderer();

            glm::vec4 color;
            bool isDirty = true;
            void setSprite(Sprite sprite);
            void setColor(glm::vec4 color);
            void setPosition(glm::vec2 position);
            void setScale(glm::vec2 scale);
            std::shared_ptr<Texture> getTexture();
            std::vector<glm::vec2> getTexCoords();
            void setClean();
            glm::vec2 position;
            glm::vec2 scale;
        private:
            std::unique_ptr<Sprite> mSprite;
    };
}

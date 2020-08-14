#pragma once
#include <glm/glm.hpp>
#include <bismuth/texture.hpp>
#include <vector>
#include <memory>
namespace bi {
    class Sprite {
        public:
            // constructors, asssignment, destructor
            Sprite(std::shared_ptr<Texture> texture);
            Sprite();
            ~Sprite();

            int getTextureId();
            void setTexture(Texture& texture);
            void setTexCoords(std::vector<glm::vec2>& texCoords);
            std::vector<glm::vec2> getTexCoords();
            std::shared_ptr<Texture> getTexture();

        private:
            std::shared_ptr<Texture> texture;
            void construct();
            float width, height;
            std::vector<glm::vec2> texCoords;
    };
}

#pragma once
#include <string>
namespace bi {
    class Texture {
        public:
            // constructors, asssignment, destructor
            Texture (std::string filepath);
            Texture (int w, int h) : width(w), height(h) {

            }
            Texture ();
            ~Texture ();
            void init();
            int width = 0, height = 0;

            void bind();
            void unbind();
            unsigned int textureId;
            std::string filepath;

        private:




    };
}

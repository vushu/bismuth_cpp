#pragma once
#include <string>
namespace bi {
    class Texture {
        public:
            // constructors, asssignment, destructor
            Texture (std::string filepath);
            ~Texture ();
            void init();
            int width, height;

            void bind();
            void unbind();
            unsigned int textureId;
            std::string filepath;

        private:




    };
}

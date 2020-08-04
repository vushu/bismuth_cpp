#pragma once
#include <string>
namespace bi {
    class Texture {
        public:
            // constructors, asssignment, destructor
            Texture ();
            ~Texture ();
            void init(std::string filepath);
            int width, height;

            void bind();
            void unbind();
            unsigned int textureId;


        private:
            std::string filepath;




    };
}

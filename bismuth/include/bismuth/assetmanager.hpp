#pragma once
#include <bismuth/texture.hpp>
#include <string>
#include <map>

namespace bi  {
    class AssetManager {
        public:
            // constructors, asssignment, destructor
            AssetManager ();
            ~AssetManager ();

            std::string loadTexture(std::string filepath);
            Texture& getTexture(std::string filepath);
            bool textureExists(std::string filepath);


        private:
            std::map<std::string, Texture> textures;

    };
}

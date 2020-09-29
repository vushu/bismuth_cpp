#pragma once
#include <bismuth/texture.hpp>
#include <string>
#include <map>
#include <memory>
#include <vector>

namespace bi  {
    class AssetManager {
        public:
            // constructors, asssignment, destructor
            AssetManager ();
            ~AssetManager ();

            int loadTexture(std::string filepath);
            Texture& getTexture(std::string filepath);
            Texture& getTexture(int texId);
            bool textureExists(std::string filepath);
            std::vector<Texture*>& getTextures();

        private:
            std::map<std::string, std::unique_ptr<Texture>> textures;
            std::map<int, std::string> filepaths;
            std::vector<Texture*> values;

    };
}


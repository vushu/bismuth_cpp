#pragma once
#include "bismuth/font.hpp"
#include "bismuth/texture.hpp"
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
            Font& getFont(std::string filepath);
            Font& getDefaultFont();
            bool textureExists(std::string filepath);
            std::vector<Texture*>& getTextures();
            void initDefaults();

        private:
            Font defaultFont;
            std::map<std::string, std::unique_ptr<Texture>> textures;
            std::map<std::string, std::unique_ptr<Font>> fonts;
            std::map<int, std::string> filepaths;
            std::vector<Texture*> values;

    };
}


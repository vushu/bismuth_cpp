#pragma once
#include <bismuth/texture.hpp>
#include <string>
#include <map>
#include <memory>

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

            static AssetManager& get() {
                static AssetManager instance;
                return instance;
            }

        private:
            std::map<std::string, std::unique_ptr<Texture>> textures;
            std::map<int, std::string> filepaths;

    };
    AssetManager& assetManager();
}


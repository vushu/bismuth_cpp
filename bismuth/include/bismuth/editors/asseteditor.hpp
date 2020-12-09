#pragma once
#include <bismuth/scene.hpp>
#include <bismuth/texture.hpp>
namespace bi {
    class AssetEditor : public Scene {
        public:
            // constructors, asssignment, destructor
            AssetEditor();
            ~AssetEditor();
            void update(float dt);
            void init();
            void start();
            void close();

        private:

            void drawGrid();
            Texture* currentTexture = nullptr;
            float scale = 6.0f;
            float maxScale = 10.0f;
            bool open = false;

    };
}

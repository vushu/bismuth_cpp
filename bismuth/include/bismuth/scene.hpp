#pragma once
#include <bismuth/renderer.hpp>
#include <bismuth/iomanager.hpp>
namespace bi {
    class Scene {
        public:
            Scene();
            ~Scene();
            virtual void update(float dt);
            virtual void init();
            virtual void start();
            virtual void close();
            void sceneStart();
            void sceneInit();
            std::string nextScene = "";
            bool started = false;
        protected:
            Renderer& getRenderer();
            ShapeRenderer& getShapeRenderer();
            Window& getWindow();
            Camera& getCamera();
            AudioManager& getAudioManager();
            AssetManager& getAssetManager();
            GuiManager& getGuiManager();
            TiledManager& getTileManager();

        private:

    };
}

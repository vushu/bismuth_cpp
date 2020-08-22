#pragma once
#include "bismuth/textrenderer.hpp"
#include <bismuth/camera.hpp>
//#include <bismuth/renderer.hpp>
#include <bismuth/renderino.hpp>
#include <bismuth/window.hpp>
#include <bismuth/audiomanager.hpp>
#include <bismuth/assetmanager.hpp>
#include <bismuth/guimanager.hpp>

#include <memory>

namespace bi {
    class Application{
        public:
            // constructors, asssignment, destructor
            Application();
            Application(int width, int height, std::string title);
            ~Application();
            void loop();
            void run();

            Renderino& getRenderer();
            Window& getWindow();
            Camera& getCamera();
            AudioManager& getAudioManager();
            AssetManager& getAssetManager();
            GuiManager& getGuiManager();
            //static void emscriptenloop(void* arg);
        protected:

            virtual void update(float dt);
            virtual void init();
        private:
            //std::unique_ptr<Renderer> renderer;
            std::unique_ptr<Renderino> renderer;
            std::unique_ptr<Window> window;
            std::unique_ptr<Camera> camera;
            std::unique_ptr<AudioManager> audioManager;
            std::unique_ptr<AssetManager> assetmanager;
            std::unique_ptr<GuiManager> guimanager;
            //std::unique_ptr<TextRenderer> textrenderer;

            void construct(int width, int height, std::string title);
            void applicationInit();
            void nativeLoop();
            std::string title;
            float beginTime;
            float endTime;
            float dt;


    };
}

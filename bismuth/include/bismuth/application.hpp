#pragma once
#include <bismuth/camera.hpp>
#include <bismuth/renderer.hpp>
#include <bismuth/window.hpp>
#include <bismuth/audiomanager.hpp>
#include <bismuth/assetmanager.hpp>
#include <bismuth/guimanager.hpp>
#include <bismuth/framebuffer.hpp>
#include <bismuth/scenemanager.hpp>
#include <bismuth/iomanager.hpp>

#include <memory>

namespace bi {
    class Application {
        public:
            // constructors, asssignment, destructor
            Application();
            Application(int width, int height, std::string title);
            ~Application();
            void loop();
            void run();

            Renderer& getRenderer();
            Window& getWindow();
            Camera& getCamera();
            AudioManager& getAudioManager();
            AssetManager& getAssetManager();
            GuiManager& getGuiManager();
            Framebuffer& getMainFramebuffer();

        protected:

            virtual void update(float dt);
            virtual void init();
        private:
            std::unique_ptr<IOManager> ioManager;
            //std::unique_ptr<Renderer> renderer;
            //std::unique_ptr<Window> window;
            //std::unique_ptr<Camera> camera;
            //std::unique_ptr<AudioManager> audioManager;
            //std::unique_ptr<AssetManager> assetmanager;
            //std::unique_ptr<GuiManager> guimanager;
            //std::unique_ptr<Framebuffer> mainFramebuffer;
            std::unique_ptr<SceneManager> scenemanager;

            void construct(int width, int height, std::string title);
            void applicationInit();
            void initOpenGL();
            void nativeLoop();
            std::string title;
            float beginTime;
            float endTime;
            float dt;


    };
}

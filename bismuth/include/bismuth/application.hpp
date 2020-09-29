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
            Application(glm::vec2 resolution, glm::vec4 tileInfo, std::string title);
            ~Application();
            void loop();
            void run();
            void fixedLoop();

            Renderer& getRenderer();
            ShapeRenderer& getShapeRenderer();
            Window& getWindow();
            Camera& getCamera();
            AudioManager& getAudioManager();
            AssetManager& getAssetManager();
            GuiManager& getGuiManager();
            Framebuffer& getMainFramebuffer();
            SceneManager& getSceneManager();
            IOManager& getIOManager();

        protected:

            virtual void update(float dt);
            virtual void init();
        private:

            const float FRAMES_PER_SEC = 1.0f/60.0f;

            float accumulated;

            //std::shared_ptr<IOManager> ioManager;
            std::unique_ptr<SceneManager> scenemanager;

            void construct(glm::vec2 resolution, glm::vec4 tileInfo, std::string title);
            void applicationInit();
            void initOpenGL();
            void nativeLoop();
            std::string title;
            float beginTime;
            float endTime;
            float dt;


    };

}

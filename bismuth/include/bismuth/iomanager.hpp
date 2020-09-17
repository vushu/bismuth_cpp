#pragma once
#include <bismuth/renderer.hpp>
#include <bismuth/shaperenderer.hpp>
#include <bismuth/window.hpp>
#include <bismuth/audiomanager.hpp>
#include <bismuth/camera.hpp>
#include <bismuth/guimanager.hpp>
#include <bismuth/framebuffer.hpp>
#include <bismuth/tiledmanager.hpp>
#include <memory>
namespace bi {

    class IOManager {
        public:
            // constructors, asssignment, destructor
            IOManager(int width, int height, std::string title);
            IOManager(glm::vec2 resolution, glm::vec4 tileInfo, std::string title);
            ~IOManager();
            void init();

            std::unique_ptr<Renderer> renderer;
            std::unique_ptr<Window> window;
            std::unique_ptr<Camera> camera;
            std::unique_ptr<AudioManager> audioManager;
            std::unique_ptr<AssetManager> assetmanager;
            std::unique_ptr<GuiManager> guimanager;
            std::unique_ptr<Framebuffer> mainFramebuffer;
            std::unique_ptr<ShapeRenderer> shaperenderer;
            std::unique_ptr<TiledManager> tiledManager;
        private:
            void construct(glm::vec2 resolution, glm::vec4 tileInfo, std::string);
    };
}

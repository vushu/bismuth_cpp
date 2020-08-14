#pragma once
#include <bismuth/camera.hpp>
#include <bismuth/renderer.hpp>
#include <bismuth/window.hpp>
#include <bismuth/audiomanager.hpp>
#include <memory>

namespace bi {
    class Application{
        public:
            // constructors, asssignment, destructor
            Application();
            Application(int width, int height, std::string title);
            ~Application();
            void emLoop();
            void run();

            Renderer& getRenderer();
            Window& getWindow();
            Camera& getCamera();
            //static void emscriptenloop(void* arg);
        protected:
            std::unique_ptr<Renderer> renderer;
            std::unique_ptr<Window> window;
            std::unique_ptr<Camera> camera;
            std::unique_ptr<AudioManager> audioManager;

            virtual void update(float dt);
            virtual void init();
        private:

            void construct(int width, int height, std::string title);
            void applicationInit();
            void loop();
            std::string title;
            float beginTime;
            float endTime;
            float dt;


    };
}

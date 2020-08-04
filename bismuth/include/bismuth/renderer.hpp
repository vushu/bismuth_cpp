#pragma once
#include <bismuth/shader.hpp>
#include <bismuth/window.hpp>
#include <bismuth/camera.hpp>
#include <bismuth/renderbatch.hpp>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
//#include <entt/entt.hpp>
#include <vector>
namespace bi {
    class Renderer {
        public:
            Renderer(std::unique_ptr<Window>& win, Camera& cam) : camera(cam), window(win) {}
            ~Renderer();
            void init();
            void clear(float r, float g, float b, float a);
            void clear(glm::vec4 color);
            //void render(float dt, entt::registry& registry);
        private:
            Camera& camera;
            std::unique_ptr<Window>& window;
            const int MAX_BATCH_SIZE = 1000;
            std::vector<RenderBatch> batches;
    };
}

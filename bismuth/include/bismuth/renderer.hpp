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
            Renderer(std::unique_ptr<Window>& win, std::unique_ptr<Camera>& cam) : camera(cam), window(win) {
                this->shader = std::make_shared<Shader>("resources/assets/shaders/default.glsl");
                //testTriangle
                //this->shader = std::make_shared<Shader>("resources/assets/shaders/texture.glsl");
                //this->textureTest = std::make_shared<Texture>("resources/assets/images/awesomeface.png");
            }
            ~Renderer();
            void init();
            void clear(float r, float g, float b, float a);
            void clear(glm::vec4 color);
            void addSprite(std::unique_ptr<SpriteRenderer> sprite);
            void render(float dt);
        private:
            std::unique_ptr<Camera>& camera;
            std::unique_ptr<Window>& window;
            const int MAX_BATCH_SIZE = 1000;
            std::shared_ptr<Shader> shader;
            std::vector<std::unique_ptr<RenderBatch>> batches;
            std::shared_ptr<Texture> textureTest;

            void testTriangle();
            void renderTestTriangle();
            void testTexture();
            void renderTestTexture();
    };
}

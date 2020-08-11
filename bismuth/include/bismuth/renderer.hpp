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
    struct RenId
    {
        int batchId;
        int spriteId;
    };
    class Renderer {
        public:
            Renderer(std::unique_ptr<Window>& win, std::unique_ptr<Camera>& cam) : camera(cam), window(win) {
                this->shader = std::make_shared<Shader>("resources/assets/shaders/default.glsl");
            }
            ~Renderer();
            void init();
            void clear(float r, float g, float b, float a);
            void clear(glm::vec4 color);
            RenId addSprite(std::shared_ptr<SpriteRenderer> sprite);
            SpriteRenderer& getSprite(int batchId, int spriteId);
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

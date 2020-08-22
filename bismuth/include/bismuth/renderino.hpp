#pragma once
#include "glm/fwd.hpp"
#include <array>
#include <bismuth/spriterenderer.hpp>
//#include <glm/glm.hpp>
#include <glad/glad.h>
#include <cstddef>
#include <bismuth/primitives.hpp>
#include <bismuth/shader.hpp>
#include <bismuth/camera.hpp>
namespace bi {

    class Renderino{

        public:
            struct RenderStats {
                uint32_t drawCount = 0;
                uint32_t quadCount = 0;
            };

            struct RendererData
            {
                GLuint quadVA = 0;
                GLuint quadVB = 0;
                GLuint quadIB = 0;

                GLuint whiteTexture = 0;
                uint32_t whiteTextureSlot = 0;

                uint32_t indexCount = 0;

                QuadVertex* quadBuffer = nullptr;
                QuadVertex* currentLocationPtr = nullptr;

                std::array<uint32_t, 8> textureSlots;
                uint32_t textureSlotsIndex = 1;

                RenderStats stats;

            };

            // constructors, asssignment, destructor
            Renderino(Camera& cam): camera(cam) {}
            ~Renderino();
            void init();
            void beginBatch();
            void endBatch();
            void flush();
            void drawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color);
            void draw(SpriteRenderer& sprite);
            void resetStats();
            void clear(glm::vec4 color);
            void clear(float r, float g, float b, float a);
            RenderStats& getRenderStats();
        private:
            static const size_t maxQuadCount = 1000;
            static const size_t maxVertexCount = maxQuadCount * 4;
            static const size_t maxIndexCount = maxQuadCount * 6;
            static const size_t maxTextures = 8;
            std::array<float, maxVertexCount> vertices;

            RendererData s_renderData;
            Shader shader{"resources/assets/shaders/default.glsl"};

            Camera& camera;
    };

}

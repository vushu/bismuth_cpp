#pragma once
#include "bismuth/texture.hpp"
#include "glm/fwd.hpp"
#include <array>
//#include <bismuth/spriterenderer.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <cstddef>
#include <bismuth/primitives.hpp>
#include <bismuth/shader.hpp>
#include <bismuth/camera.hpp>

#include <bismuth/font.hpp>
#include <set>
#include <tuple>
#include <vector>
namespace bi {

    class Renderer {

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
                std::array<uint32_t, 8> textureIds;
                uint32_t textureSlotsIndex = 0;
                RenderStats stats;

            };

            // constructors, asssignment, destructor
            Renderer(Camera& cam): camera(cam) {}
            ~Renderer();
            void init();
            //Starting a batch
            void beginBatch();
            void endBatch();
            //Sending all data to the GPU
            void flush();

            void drawTexture(glm::vec2 pos, glm::vec2 size, glm::vec4 color, int texId, float angle, std::array<glm::vec2, 4> texCoords = defaultTexcoords);
            void drawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color, float angle);
            void drawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color);
            void drawText(std::string text, Font& f);
            //void draw(SpriteRenderer& sprite);
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

            glm::vec2 rotatePoint(const glm::vec2& pos, float angle);
            RendererData s_renderData;
            Shader shader{"resources/assets/shaders/default.glsl"};

            static constexpr std::array<glm::vec2, 4> defaultTexcoords = {
                glm::vec2(1.0f, 1.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(0.0f, 0.0f),
                glm::vec2(0.0f, 1.0f)
            };

            static constexpr int textureSlots[8] = { 0, 1, 2, 3, 4, 5, 6, 7};

            Camera& camera;

            void setQuadVertex(QuadVertex*& quadVertex,glm::vec2 position, glm::vec2 size, glm::vec2 texcoord, glm::vec4 color, float texId);
            void setQuadVertices(QuadVertex*& quadVertex, glm::vec2 position, glm::vec2 size, glm::vec4 color, float texId, float angle, std::array<glm::vec2, 4> texCoords = defaultTexcoords);
            void incrementDrawCounters();
            void reevaluateBatchSpace();
            std::array<glm::vec2, 4> getCorners(glm::vec2 position, glm::vec2 size, float angle);

    };
}

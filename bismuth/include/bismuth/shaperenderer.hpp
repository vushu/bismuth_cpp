#pragma once
#include "glm/fwd.hpp"
#include "primitives.hpp"
#include <glad/glad.h>
#include <bismuth/shader.hpp>
#include <bismuth/camera.hpp>
namespace bi {
    class ShapeRenderer{

        struct ShaperRenderData {
            GLuint quadVA = 0;
            GLuint quadVB = 0;
            GLuint quadIB = 0;

            SimpleVertex* vertexBuffer = nullptr;
            SimpleVertex* currentLocationPtr = nullptr;
            int vertexCounter = 0;
        };

        public:
            // constructors, asssignment, destructor
            ShapeRenderer(Camera& cam) : camera(cam) {}
            ~ShapeRenderer();

            void init();
            void drawLine(glm::vec2 posFrom, glm::vec2 posTo, glm::vec4 color);
            void drawPolygon(glm::vec2 centerPos, float radius, int segments, glm::vec4 color, float angle, bool centerShown = false);
            void flush();

        private:
            Camera& camera;
            Shader shader{"resources/assets/shaders/shape.glsl"};
            ShaperRenderData renderData;
            unsigned int maxVertexCount = 1000;
            void setVertex(glm::vec2 position, glm::vec4);
            glm::vec2 rotatePoint(const glm::vec2& pos, float angle);

    };
}

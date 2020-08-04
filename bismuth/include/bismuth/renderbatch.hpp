#pragma once
#include <bismuth/shader.hpp>
#include <bismuth/camera.hpp>
#include <memory>
namespace bi {
    class RenderBatch {
        public:
            // constructors, asssignment, destructor
            RenderBatch (Camera& cam, int maxBatchSize) : camera(cam), maxBatchSize(maxBatchSize) {}
            ~RenderBatch ();
            bool hasRoom = true;
            int numberOfSprite = 0;

            std::vector<float> vertices;

            //Vertex definition
            //========
            //Pos              color                          tex coords    tex id
            // float, float,   float, float , float , float   float, float   float
        private:
            Camera& camera;
            int maxBatchSize;
            const int POS_SIZE = 2;
            const int COLOR_SIZE = 4;
            const int TEX_COORDS_SIZE = 2;
            const int TEX_ID_SIZE = 1;

            // OFFSETS
            const int POS_OFFSET = 0;
            const int COLOR_OFFSET = POS_OFFSET + POS_SIZE * sizeof(float);
            const int TEX_COORDS_OFFSET = COLOR_OFFSET + COLOR_SIZE * sizeof(float);
            const int TEX_ID_OFFSET = TEX_COORDS_OFFSET + TEX_COORDS_SIZE * sizeof(float);

            // VERTEX SIZE
            const int VERTEX_SIZE = 9;
            const int VERTEX_SIZE_BYTES = VERTEX_SIZE * sizeof(float);

            Shader shader{"default.glsl"};

            std::vector<int> generateIndices();

            void loadElementIndices(std::vector<int>& elements, int index);
    };
}

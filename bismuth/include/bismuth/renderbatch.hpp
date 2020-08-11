#pragma once
#include <bismuth/spriterenderer.hpp>
#include <bismuth/shader.hpp>
#include <bismuth/camera.hpp>
#include <memory>
#include <array>
namespace bi {
    class RenderBatch {
        public:
            struct compare
            {
                Texture key;
                compare(Texture const &i): key(i) { }

                bool operator()(Texture const &i)
                {
                    return (i.textureId == key.textureId);
                }
            };

            // constructors, asssignment, destructor
            RenderBatch (std::unique_ptr<Camera>& cam, int maxBatchSize, std::shared_ptr<Shader> shader) : camera(cam) {
                //this->shader = std::make_unique<Shader>("resources/assets/shaders/default.glsl");
                //this->shader->compile();
                this->shader = shader;
            }
            ~RenderBatch ();
            bool hasRoom = true;
            int numberOfSprite = 0;

            //maxBatchSize * 4 * 9
            std::array<float, 36000> vertices;

            std::vector<std::unique_ptr<SpriteRenderer>> sprites;
            std::vector<std::shared_ptr<Texture>> textures;

            void init();
            void addSprite(std::unique_ptr<SpriteRenderer> spriteRenderer);
            void render();
            //Vertex definition
            //========
            //Pos              color                          tex coords    tex id
            // float, float,   float, float , float , float   float, float   float
        private:
            std::unique_ptr<Camera>& camera;
            int maxBatchSize = 1000;
            const float POS_SIZE = 2;
            const float COLOR_SIZE = 4;
            const float TEX_COORDS_SIZE = 2;
            const float TEX_ID_SIZE = 1;
            int texSlots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

            // OFFSETS
            const int POS_OFFSET = 0;
            const unsigned int COLOR_OFFSET = POS_OFFSET + POS_SIZE * sizeof(float);
            const unsigned int TEX_COORDS_OFFSET = COLOR_OFFSET + COLOR_SIZE * sizeof(float);
            const unsigned int TEX_ID_OFFSET = TEX_COORDS_OFFSET + TEX_COORDS_SIZE * sizeof(float);

            //VERTEX IDS
            unsigned int vaoId, vboId;
            int zIndex;

            // VERTEX SIZE
            const int VERTEX_SIZE = 9;
            const int VERTEX_SIZE_BYTES = VERTEX_SIZE * sizeof(float);

            std::shared_ptr<Shader> shader;

            std::array<unsigned int, 6000> generateIndices();

            void loadElementIndices(std::array<unsigned int, 6000>& elements, int index);
            void loadVertexProperties(int index);

    };
}

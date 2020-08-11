#include <bismuth/logging.hpp>
#include <glad/glad.h>
#include <bismuth/renderbatch.hpp>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
// glm to string
//#include <glm/gtx/string_cast.hpp>

using namespace bi;

RenderBatch::~RenderBatch() {
    bi::log("Batch destroyed");
}


std::array<unsigned int, 6000> RenderBatch::generateIndices() {
    // 6 * 1000
    std::array<unsigned int, 6000> elements;
    for (int i = 0; i < maxBatchSize; i++) {
        loadElementIndices(elements, i);
    }

    return elements;
}

void RenderBatch::loadElementIndices(std::array<unsigned int, 6000>& elements, int index) {
    int offsetArrayIndex = 6 * index;
    int offset = 4 * index;

    elements[offsetArrayIndex] = offset + 3;
    elements[offsetArrayIndex + 1] = offset + 2;
    elements[offsetArrayIndex + 2] = offset + 0;

    elements[offsetArrayIndex + 3] = offset + 0;
    elements[offsetArrayIndex + 4] = offset + 2;
    elements[offsetArrayIndex + 5] = offset + 1;
}

void RenderBatch::loadVertexProperties(int index) {
    auto& sprite = this->sprites.at(index);
    if (sprite == nullptr) {
        throw std::runtime_error("failed");
    }
    int offset = index * 4 * VERTEX_SIZE;
    std::vector<glm::vec2> texCoords = sprite->getTexCoords();
    glm::vec4 color = sprite->color;
    int texId = 0;
    if (sprite->getTexture() != nullptr) {
        for (long i = 0; i < textures.size(); i++) {
            if (textures.at(i) == sprite->getTexture()) {
                texId = i + 1;
                log("Found: texId " + std::to_string(texId));
                break;
            }
        }
    }

    float xAdd = 1.0f;
    float yAdd = 1.0f;

    for (int i = 0; i < 4; i++) {
        if (i == 1) {
            yAdd = 0.0f;
        }
        else if (i == 2) {
            xAdd = 0.0f;
        }
        else if (i == 3){
            yAdd = 1.0f;
        }

        // Load position of the GameObject
        vertices[offset] = sprite->position.x + (xAdd * sprite->scale.x);

        vertices[offset + 1] = sprite->position.y + (yAdd * sprite->scale.y);

        //Load color
        vertices[offset + 2] = color.x;
        vertices[offset + 3] = color.y;
        vertices[offset + 4] = color.z;
        vertices[offset + 5] = color.w;

        //bi::log("color x " +  std::to_string(vertices[offset + 2]));
        //bi::log("color y " +  std::to_string(vertices[offset + 3]));
        //bi::log("color z " +  std::to_string(vertices[offset + 4]));
        //bi::log("color w " +  std::to_string(vertices[offset + 5]));

        // Load Texture Coords
        vertices[offset + 6] = texCoords[i].x;
        vertices[offset + 7] = texCoords[i].y;
        // Load Texture ID
        vertices[offset + 8] = texId;

        //log("TEX_ID " + std::to_string(texId));

        offset += VERTEX_SIZE;
    }

}

void RenderBatch::init() {

    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),0, GL_DYNAMIC_DRAW);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        // Failed
        glDeleteBuffers(1, &vboId);
        throw std::runtime_error("failed to bind buffer");
        //vbo = 0;
    }

    unsigned int eboId;
    glGenBuffers(1, &eboId);
    std::array<GLuint, 6000> indices = generateIndices();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);


    // Enabling attributes
    glVertexAttribPointer(0, POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (const GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (const GLvoid *) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, TEX_COORDS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (const GLvoid *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, TEX_ID_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (const GLvoid *) (8 * sizeof(float)));
    glEnableVertexAttribArray(3);
    bi::log("RenderBatch initialized");
}

void RenderBatch::addSprite(std::unique_ptr<SpriteRenderer> sprite) {
    this->textures.push_back(sprite->getTexture());
    this->sprites.push_back(std::move(sprite));
    loadVertexProperties(0);
    numberOfSprite++;
    //if (sprite.getTexture() != nullptr) {
    //if (std::none_of(textures.begin(), textures.end(), compare(*sprite.getTexture()))) {

    //}
    //}
}


void RenderBatch::render() {
    bool rebufferData = false;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < sprites.size(); i++) {
        auto& spr = this->sprites.at(i);
        if (spr == nullptr) {
            throw std::runtime_error("NO SPRITE");

        }
        if (spr->isDirty) {
            loadVertexProperties(i);
            spr->setClean();
            rebufferData = true;
            //log("Done cleaning");
        }
    }

    if (rebufferData) {
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        //log("Vertices size: " + std::to_string(vertices.size()));
        float datasize = (vertices.size() * sizeof(float));
        glBufferSubData(GL_ARRAY_BUFFER, 0, datasize, &vertices.front());
        GLint size = 0;
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        if(datasize != size)
        {
            glDeleteBuffers(1, &vboId);
            throw std::runtime_error("Failed to glbuffersubdata "+  std::to_string(datasize) + " != " + std::to_string(size));
        }
        else{
            log("BUFFER IS OK!");
        }

    }

    shader->use();


    shader->uploadUniformMat4("uProjection", camera->projectionMatrix);
    shader->uploadUniformMat4("uView", camera->viewMatrix);
    //bi::log("CAMERA");
    //bi::log(glm::to_string(camera->projectionMatrix));
    //bi::log(glm::to_string(camera->viewMatrix));
    //bi::log("CAMERA END");

    // activate texture slots
    for (long i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i + 1);
        textures.at(i)->bind();
    }

    //glActiveTexture(GL_TEXTURE0);
    //textures.at(0)->bind();

    //bi::log("SHADER ID: " + std::to_string(shader->shaderProgramId));
    //
    //shader->uploadUniformInt("uTex", 0);
    /// setting sample to correct id which is GL_TEXTURE0
    //glUniform1i(glGetUniformLocation(shader->shaderProgramId, "uTex"), 0);
    //shader->uploadUniformInt("uTex", 0); // Texture0 which is why 0
    shader->uploadIntArray("uTextures", 8, &this->texSlots[0]);
    //shader->uploadIntArray2("uTextures", 8, &this->texSlots[0]);
    //glUniform1iv(glGetUniformLocation(shader->shaderProgramId, "uTextures"), 8, this->texSlots);

    glBindVertexArray(vaoId);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, numberOfSprite * 6, GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_TRIANGLES,  6, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);

    for (auto& tex : textures) {
        tex->unbind();
    }
    shader->detach();

}




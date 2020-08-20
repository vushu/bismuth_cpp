#include <glm/ext/scalar_constants.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <bismuth/logging.hpp>
#include <glad/glad.h>
#include <bismuth/renderbatch.hpp>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
// glm to string
#include <glm/gtx/string_cast.hpp>

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
    //int offset = index * 4 * VERTEX_SIZE;
    std::vector<glm::vec2> texCoords = sprite->getTexCoords();
    glm::vec4 color = sprite->color;
    int texId = 0;
    if (sprite->getTextureFilePath() != "") {
        for (unsigned int i = 0; i < textures.size(); i++) {
            if (textures.at(i)->filepath == sprite->getTextureFilePath()) {
                texId = i + 1;
                //log("Found: texId " + std::to_string(texId));
                break;
            }
        }
    }
    //else {
    //log("no texture");
    //}

    int offsetVerts = index * 4 * VERTEX_SIZE;
    //rotation
    glm::vec2 halfDims(sprite->scale / 2.0f);
    glm::vec2 tl(-halfDims.x, halfDims.y);
    glm::vec2 bl(-halfDims.x, -halfDims.y);
    glm::vec2 br(halfDims.x, -halfDims.y);
    glm::vec2 tr(halfDims.x, halfDims.y);

    //if index 0 then offset is 0
    // Load position of the GameObject
    //vertices[offset] = sprite->position.x + (xAdd * sprite->scale.x);

    //vertices[offset + 1] = sprite->position.y + (yAdd * sprite->scale.y);
    float angle = sprite->angleDegrees;

    glm::vec2 topLeft = rotatePoint(tl, angle) + halfDims + sprite->position;
    glm::vec2 botLeft = rotatePoint(bl, angle) + halfDims + sprite->position;
    glm::vec2 botRight = rotatePoint(br, angle) + halfDims + sprite->position;
    glm::vec2 topRight = rotatePoint(tr, angle) + halfDims + sprite->position;

    vertices[offsetVerts] = botRight.x;
    vertices[offsetVerts + 1] = botRight.y;

    vertices[offsetVerts + 1 * VERTEX_SIZE] = topRight.x;
    vertices[offsetVerts + 1 * VERTEX_SIZE + 1] = topRight.y;

    vertices[offsetVerts + 2 * VERTEX_SIZE] = topLeft.x;
    vertices[offsetVerts + 2 * VERTEX_SIZE + 1] = topLeft.y;
    //
    vertices[offsetVerts + 3 * VERTEX_SIZE] = botLeft.x;
    vertices[offsetVerts + 3 * VERTEX_SIZE + 1] = botLeft.y;
    //

    int offset = index * 4 * VERTEX_SIZE;
    for (int i = 0; i < 4; i++) {

        //Load color
        vertices[offset + 2] = color.x;
        vertices[offset + 3] = color.y;
        vertices[offset + 4] = color.z;
        vertices[offset + 5] = color.w;


        // Load Texture Coords
        vertices[offset + 6] = texCoords[i].x;
        vertices[offset + 7] = texCoords[i].y;
        // Load Texture ID
        vertices[offset + 8] = texId;
        //log("INDEX: "  + std::to_string(texId));
        //log("INDEX: "  + std::to_string(index));
        //vertices[offset + 9] = index; // id of the model

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

    //glVertexAttribPointer(4, MODEL_ID_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (const GLvoid *) (9 * sizeof(float)));
    //glEnableVertexAttribArray(4);
    bi::log("RenderBatch initialized");
}

int RenderBatch::addSprite(std::shared_ptr<SpriteRenderer> sprite) {
    if (sprite->getTextureFilePath() != "") {
        if (this->checkList.count(sprite->getTextureFilePath()) == 0) {
            this->checkList.emplace(sprite->getTextureFilePath(), "");
            log("Adding sprite: " + sprite->getTextureFilePath());
            this->textures.push_back(&assetmanager.getTexture(sprite->getTextureFilePath()));
        }
    }
    this->sprites.push_back(sprite);
    log("Added sprite");
    loadVertexProperties(this->sprites.size() - 1);
    numberOfSprite++;
    if (numberOfSprite == 1000) {
        this->hasRoom = false;
    }
    return sprites.size() - 1;
}


void RenderBatch::render() {
    bool rebufferData = false;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (unsigned int i = 0; i < sprites.size(); i++) {
        auto& spr = this->sprites.at(i);
        if (spr == nullptr) {
            throw std::runtime_error("NO SPRITE");
        }

        if (spr->isDirty) {
            loadVertexProperties(i);
            spr->setClean();
            rebufferData = true;
            //log("Rebuffer");
        }
    }

    if (rebufferData) {
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        //log("Vertices size: " + std::to_string(vertices.size()));
        float datasize = (vertices.size() * sizeof(float));
        glBufferSubData(GL_ARRAY_BUFFER, 0, datasize, &vertices.front());
        // check if success
        GLint size = 0;
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        if(datasize != size) {
            glDeleteBuffers(1, &vboId);
            throw std::runtime_error("Failed to glbuffersubdata "+  std::to_string(datasize) + " != " + std::to_string(size));
        }

    }

    shader->use();

    shader->uploadUniformMat4("uProjection", camera->projectionMatrix);
    shader->uploadUniformMat4("uView", camera->viewMatrix);

    //std::vector<glm::mat4> models;
    //rotation
    //set set i needed to update
    //float new_value = 5.f;
    //GLint foo5_loc = glGetUniformLocation(progId, "foo[5]");
    //glUniform1fv(foo5_loc, 1, &new_value);
    //log("Sprites: " + std::to_string(sprites.size()));
    //for (auto& spr : sprites) {
    //log(glm::to_string(spr->scale));
    //glm::mat4 model = glm::mat4(1.0f);
    //if (spr->angleDegrees != 0) {
    //// the vector between 0,0 and position
    //glm::vec2 dis = glm::vec2(0,0) - spr->position;
    //// moving it to position
    //model = glm::translate(model, glm::vec3(spr->position, 0.0f));
    //// moving it the half the size back
    //model = glm::translate(model, glm::vec3(spr->scale * 0.5f,0));
    //model = glm::rotate(model, glm::radians(spr->angleDegrees), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    //// Then rotate
    ////translating midle to 0.0
    //model = glm::translate(model, glm::vec3(dis - spr->scale * 0.5f,0));
    //when doing glm read from below and up
    //shader->uploadUniformMat4("uModel", model);
    //}
    //models.push_back(model);
    //}

    //log("model: " + std::to_string(models.size()));

    //for (glm::mat4 m : models) {
    //log("Models: " + glm::to_string(m));
    //}
    GLint maxUniformVectors;
    glGetIntegeri_v(GL_MAX_VERTEX_UNIFORM_VECTORS,1, &maxUniformVectors);
    log("maxUniforms: " + std::to_string(maxUniformVectors));
    log("sprites: " + std::to_string(sprites.size()));
    //upload models
    //glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgramId, "uModels"), models.size(), GL_FALSE, glm::value_ptr(models[0]));


    // activate texture slots
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i + 1);
        textures.at(i)->bind();
    }

    shader->uploadIntArray("uTextures", 8, &this->texSlots[0]);

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

glm::vec2 RenderBatch::rotatePoint(const glm::vec2& pos, float angle) {
    glm::vec2 newPos;
    newPos.x = pos.x * cos(angle) - pos.y * sin(angle);
    newPos.y = pos.x * sin(angle) + pos.y * cos(angle);
    return newPos;
}






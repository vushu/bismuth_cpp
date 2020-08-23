#include <bismuth/spriterenderer.hpp>
#include <array>
#include <bismuth/renderer.hpp>
#include <cstring>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <bismuth/logging.hpp>
#include "bismuth/primitives.hpp"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace bi;

void checkGLError()
{
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR){
        std::cout << err;
        throw std::runtime_error("ERROR");
    }
}

void Renderer::init()  {

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        log("Renderer: Failed to initialize GLAD");
        throw std::runtime_error("Renderer: Failed to initialize GLAD");
    }
    //font
    //glEnable(GL_CULL_FACE);
    // alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    this->shader.compile();



    s_renderData.quadBuffer = new QuadVertex[maxVertexCount];

    glGenVertexArrays(1, &s_renderData.quadVA);
    glBindVertexArray(s_renderData.quadVA);

    glGenBuffers(1, &s_renderData.quadVB);
    glBindBuffer(GL_ARRAY_BUFFER, s_renderData.quadVB);
    //reserving buffer of maxVertexCount
    glBufferData(GL_ARRAY_BUFFER, maxVertexCount * sizeof(QuadVertex) , nullptr, GL_DYNAMIC_DRAW);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        // Failed
        glDeleteBuffers(1, &s_renderData.quadVB);
        throw std::runtime_error("Failed to bind buffer");
        //vbo = 0;
    }

    // Enabling attributes
    // position
    //
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const GLvoid *) offsetof(QuadVertex, position));
    //color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const GLvoid *) offsetof(QuadVertex, color));
    //texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex),  (const GLvoid *) offsetof(QuadVertex, texcoords));
    //texId
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const GLvoid *) offsetof(QuadVertex, texId));

    //Create indices
    uint32_t indices[maxIndexCount];
    uint32_t offset = 0;

    for (int i = 0; i < maxIndexCount; i += 6) {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 3 + offset;

        indices[i + 3] = 1 + offset;
        indices[i + 4] = 2 + offset;
        indices[i + 5] = 3 + offset;


        /*
           indices[i + 0] = 3 + offset;
           indices[i + 1] = 2 + offset;
           indices[i + 2] = 0 + offset;

           indices[i + 3] = 0 + offset;
           indices[i + 4] = 2 + offset;
           indices[i + 5] = 1 + offset;

*/
        offset += 4;
    }

    glGenBuffers(1, &s_renderData.quadIB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_renderData.quadIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //Done generating
    //Batch data
    log("Batch data initialized");

    GLenum erre = glGetError();
    if (erre != GL_NO_ERROR) {
        log("ERROR: !!" + std::to_string(erre));
    }

}



void Renderer::beginBatch() {
    //log("*************** begin batch ******************");
    s_renderData.currentLocationPtr = s_renderData.quadBuffer;
    //s_renderData.indexCount = 0;

}

void Renderer::endBatch() {

    GLsizeiptr size = (uint8_t*) this->s_renderData.currentLocationPtr - (uint8_t*) this->s_renderData.quadBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, s_renderData.quadVB);
    //log("Size of buffer:" + std::to_string(size));
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_renderData.quadBuffer);
}

glm::vec2 Renderer::rotatePoint(const glm::vec2& pos, float angle) {
    glm::vec2 newPos;
    newPos.x = pos.x * cos(angle) - pos.y * sin(angle);
    newPos.y = pos.x * sin(angle) + pos.y * cos(angle);
    return newPos;
}

void Renderer::drawTexture(glm::vec2 pos, glm::vec2 size, glm::vec4 color, int texId, float angle) {

    if (s_renderData.indexCount >= maxIndexCount || s_renderData.textureSlotsIndex >= 8) {
        endBatch();
        flush();
        beginBatch();
    }

    float textureIndex = 0.0f;
    for (int i = 0; i < maxTextures; i++) {
        if (textureIds[i] == texId) {
            textureIndex = i + 1;
            log("BREAK");
            break;
        }
    }

    if (textureIndex == 0.0f) {
        textureIndex = s_renderData.textureSlotsIndex;
        textureIds[s_renderData.textureSlotsIndex] = texId;
        // not existing
        s_renderData.textureSlotsIndex++;
    }

    glm::vec2 halfDims(size * 0.5f);
    glm::vec2 tl(-halfDims.x, halfDims.y);
    glm::vec2 bl(-halfDims.x, -halfDims.y);
    glm::vec2 br(halfDims.x, -halfDims.y);
    glm::vec2 tr(halfDims.x, halfDims.y);

    glm::vec2 topLeft = rotatePoint(tl, angle) + halfDims + pos;
    glm::vec2 botLeft = rotatePoint(bl, angle) + halfDims + pos;
    glm::vec2 botRight = rotatePoint(br, angle) + halfDims + pos;
    glm::vec2 topRight = rotatePoint(tr, angle) + halfDims + pos;

    setQuadVertex(s_renderData.currentLocationPtr, botRight, size, {1.0f, 1.0f}, color, texId, angle);
    this->s_renderData.currentLocationPtr++;
    setQuadVertex(s_renderData.currentLocationPtr, topRight, size, {1.0f, 0.0f}, color, texId, angle);
    this->s_renderData.currentLocationPtr++;
    setQuadVertex(s_renderData.currentLocationPtr, topLeft, size, {0.0f, 0.0f}, color, texId, angle);
    this->s_renderData.currentLocationPtr++;
    setQuadVertex(s_renderData.currentLocationPtr, botLeft, size, {0.0f, 1.0f}, color, texId, angle);
    this->s_renderData.currentLocationPtr++;

    s_renderData.indexCount += 6;
    s_renderData.stats.quadCount++;

}

void Renderer::setQuadVertex(QuadVertex* quadVertex, glm::vec2 position, glm::vec2 size, glm::vec2 texCoords, glm::vec4 color, int texId, float angle) {
    quadVertex->position = { position, 0.0f};
    quadVertex->color = color;
    quadVertex->texcoords = texCoords;
    quadVertex->texId = texId;
}


void Renderer::drawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color, float angle) {

    if (s_renderData.indexCount >= maxIndexCount) {
        endBatch();
        flush();
        beginBatch();
    }

    int texId = 0;
    glm::vec2 halfDims(size * 0.5f);
    glm::vec2 tl(-halfDims.x, halfDims.y);
    glm::vec2 bl(-halfDims.x, -halfDims.y);
    glm::vec2 br(halfDims.x, -halfDims.y);
    glm::vec2 tr(halfDims.x, halfDims.y);

    glm::vec2 topLeft = rotatePoint(tl, angle) + halfDims + pos;
    glm::vec2 botLeft = rotatePoint(bl, angle) + halfDims + pos;
    glm::vec2 botRight = rotatePoint(br, angle) + halfDims + pos;
    glm::vec2 topRight = rotatePoint(tr, angle) + halfDims + pos;

    setQuadVertex(s_renderData.currentLocationPtr, botRight, size, {1.0f, 1.0f}, color, texId, angle);
    this->s_renderData.currentLocationPtr++;
    setQuadVertex(s_renderData.currentLocationPtr, topRight, size, {1.0f, 0.0f}, color, texId, angle);
    this->s_renderData.currentLocationPtr++;
    setQuadVertex(s_renderData.currentLocationPtr, topLeft, size, {0.0f, 0.0f}, color, texId, angle);
    this->s_renderData.currentLocationPtr++;
    setQuadVertex(s_renderData.currentLocationPtr, botLeft, size, {0.0f, 1.0f}, color, texId, angle);
    this->s_renderData.currentLocationPtr++;

    s_renderData.indexCount += 6;
    s_renderData.stats.quadCount++;

}

void Renderer::drawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color) {

    if (s_renderData.indexCount >= maxIndexCount) {

        endBatch();
        flush();
        beginBatch();
        //log("Max reached flushed");
    }

    //log("*************************************************");
    this->s_renderData.currentLocationPtr->position = {pos.x + size.x, pos.y + size.y , 0.0f};
    this->s_renderData.currentLocationPtr->color = color;
    this->s_renderData.currentLocationPtr->texcoords = { 1.0f, 1.0f};
    this->s_renderData.currentLocationPtr->texId = 0;
    this->s_renderData.currentLocationPtr++;


    this->s_renderData.currentLocationPtr->position = {pos.x + size.x, pos.y, 0.0f};
    this->s_renderData.currentLocationPtr->color = color;
    this->s_renderData.currentLocationPtr->texcoords = {1.0f, 0.0f};
    this->s_renderData.currentLocationPtr->texId = 0;
    this->s_renderData.currentLocationPtr++;


    this->s_renderData.currentLocationPtr->position = {pos.x, pos.y, 0.0f};
    this->s_renderData.currentLocationPtr->color = color;
    this->s_renderData.currentLocationPtr->texcoords = {0.0f, 0.0f};
    this->s_renderData.currentLocationPtr->texId = 0;
    s_renderData.currentLocationPtr++;

    this->s_renderData.currentLocationPtr->position = {pos.x, pos.y + size.y, 0.0f};
    this->s_renderData.currentLocationPtr->color = color;
    this->s_renderData.currentLocationPtr->texcoords = { 0.0f, 1.0f};
    this->s_renderData.currentLocationPtr->texId = 0;
    s_renderData.currentLocationPtr++;

    //log("draw called");
    s_renderData.indexCount += 6;
    s_renderData.stats.quadCount++;
}

void Renderer::flush() {

    shader.use();
    shader.uploadUniformMat4("uMvp", camera.projectionMatrix * camera.viewMatrix);


    for (int i = 0; i < s_renderData.textureSlotsIndex; i++) {
        glActiveTexture(GL_TEXTURE0 + i + 1);
        glBindTexture(GL_TEXTURE_2D, textureIds.at(i));
    }

    shader.uploadIntArray("uTextures", 8, textureSlots);

    glBindVertexArray(s_renderData.quadVA);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, s_renderData.indexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);

    for (int i = 0; i < s_renderData.textureSlotsIndex; i++) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    shader.detach();

    s_renderData.stats.drawCount++;
    s_renderData.indexCount = 0;
    s_renderData.textureSlotsIndex = 0;

    textureIds = std::array<uint32_t, 8>();
}

void Renderer::resetStats() {
    memset(&s_renderData.stats, 0, sizeof(RenderStats));
}

bi::Renderer::RenderStats& Renderer::getRenderStats () {
    return this->s_renderData.stats;
}

Renderer::~Renderer(){

    log("Destroyed Renderer!");
    delete[] s_renderData.quadBuffer;
}

void Renderer::clear(glm::vec4 color) {
    clear(color.x, color.y, color.z, color.w);
}

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}






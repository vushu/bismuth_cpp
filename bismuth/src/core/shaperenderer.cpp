#include "bismuth/primitives.hpp"
#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include <bismuth/shaperenderer.hpp>
#include <bismuth/logging.hpp>
#include <glad/glad.h>
#include <string>

using namespace bi;

ShapeRenderer::~ShapeRenderer() {}

void ShapeRenderer::init() {
    this->shader.compile();


    renderData.vertexBuffer = new SimpleVertex[maxVertexCount];
    renderData.currentLocationPtr = renderData.vertexBuffer;

    glGenBuffers(1, &renderData.quadVA);
    glBindVertexArray(renderData.quadVA);

    glGenBuffers(1, &renderData.quadVB);
    glBindBuffer(GL_ARRAY_BUFFER, renderData.quadVB);

    glBufferData(GL_ARRAY_BUFFER, this->maxVertexCount * sizeof(SimpleVertex) , nullptr, GL_DYNAMIC_DRAW);

    //position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (const GLvoid *) offsetof(SimpleVertex, position));

    //color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (const GLvoid *) offsetof(SimpleVertex, color));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void ShapeRenderer::drawLine(glm::vec2 posFrom, glm::vec2 posTo, glm::vec4 color) {

    setVertex(posFrom, color);
    setVertex(posTo, color);

}

// segments >= 12 is a cicle
void ShapeRenderer::drawPolygon(glm::vec2 centerPos, float radius, int segments, glm::vec4 color, float angle, bool centerShown) {
    if (segments < 3) {
        log("Segments are too small");
        return;
    }
    float fullCicle = M_PI * 2.0f;

    //centerPos = rotatePoint(centerPos, angle);

    if (centerShown) {

        //setVertex(rotatePoint(centerPos, angle), color);
        //setVertex(rotatePoint({centerPos.x + radius,  centerPos.y}, angle), color);
    }
    //centerPos = rotatePoint(centerPos, angle);
    // reaching the start point
    glm::vec2 startPos;
    //glm::vec2 startPos = {centerRotate.x + radius, centerRotate.y};
    //startPos = rotatePoint({centerPos.x + radius, centerPos.y}, angle);

    setVertex(startPos, color);

    glm::vec2 slicePos;
    for (int i = 0; i < segments; i++) {
        float slice = fullCicle * (float) i / static_cast<float>(segments);
        slicePos = { radius * cos(slice), radius * sin(slice) };
        slicePos = rotatePoint(slicePos, angle);

        glm::vec2 pos = {slicePos.x + centerPos.x, slicePos.y + centerPos.y};
        if (i == 0) {
            startPos = pos;
        }
        if ((i + 1) % 2 == 0 )
            setVertex(pos, color);
        //setVertex(pos, color);
        // could use an element buffer instead since we are using the same vertex
        // one more to connect to the next vertex
        setVertex(pos, color);
        //setVertex(pos, color);
        if(i == segments-1) {
            setVertex(startPos, color);
        }
    }

    //setVertex(rotatePoint(startPos, angle), color);
    // reaching the start again
    setVertex(startPos, color);
    //setVertex(startPos, color);

}


void ShapeRenderer::flush() {

    GLsizeiptr size = (uint8_t*) this->renderData.currentLocationPtr - (uint8_t*) this->renderData.vertexBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, renderData.quadVB);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, renderData.vertexBuffer);

    this->shader.use();

    shader.uploadUniformMat4("uMvp", camera.projectionMatrix * camera.viewMatrix);

    glBindVertexArray(renderData.quadVA);
    //enable position
    glEnableVertexAttribArray(0);
    //enable color
    glEnableVertexAttribArray(1);

    glLineWidth(2.0f);
    glDrawArrays(GL_LINES, 0, renderData.vertexCounter);

    glDisableVertexAttribArray(0);
    //enable color
    glDisableVertexAttribArray(1);

    glBindVertexArray(0);

    shader.detach();

    renderData.currentLocationPtr = renderData.vertexBuffer;
    renderData.vertexCounter = 0;
}


void ShapeRenderer::setVertex(glm::vec2 position, glm::vec4 color) {
    renderData.currentLocationPtr->position = { position, 0};
    renderData.currentLocationPtr->color = color;
    renderData.currentLocationPtr++;
    renderData.vertexCounter++;
}

glm::vec2 ShapeRenderer::rotatePoint(const glm::vec2& pos, float angle) {
    glm::vec2 newPos;
    newPos.x = pos.x * cos(angle) - pos.y * sin(angle);
    newPos.y = pos.x * sin(angle) + pos.y * cos(angle);
    return newPos;
}


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

    checkVertexLimit();
    setVertex(posFrom, color);
    setVertex(posTo, color);

}

void ShapeRenderer::drawLine(glm::vec2 posFrom, glm::vec2 posTo, glm::vec4 color, float angle) {
    checkVertexLimit();

    glm::vec2 diff = posTo - posFrom;
    glm::vec2 rotatedDiff = rotatePoint(diff, angle);
    glm::vec2 test = rotatedDiff + 100.0f;


    setVertex(rotatedDiff, color);
    setVertex(test, color);
    //setVertex(rotatePoint(posFrom, angle), color);
    //setVertex(rotatePoint(posTo, angle), color);
}

void ShapeRenderer::checkVertexLimit() {
    if (maxVertexCount >= 1000) {
        flush();
    }
}

// segments >= 12 is a cicle
void ShapeRenderer::drawPolygon(glm::vec2 centerPos, float radius, int segments, glm::vec4 color, float angle, bool centerShown) {
    checkVertexLimit();
    if (segments < 3) {
        log("Segments are too small");
        return;
    }
    float fullCicle = M_PI * 2.0f;

    glm::vec2 startpos;

    glm::vec2 slicePos;
    for (int i = 0; i < segments; i++) {
        float slice = fullCicle * (float) i / static_cast<float>(segments);
        slicePos = rotatePoint({ radius * cos(slice), radius * sin(slice) }, angle);
        glm::vec2 pos = { slicePos.x + centerPos.x, slicePos.y + centerPos.y };
        //glm::vec2 pos = {slicePos.x + startpos.x, slicePos.y + startpos.y};
        if (i == 0) {
            startpos = pos;
            //setVertex(pos, color);
            setVertex(pos, color);
        }
        // could use an element buffer instead since we are using the same vertex
        // one more to connect to the next vertex
        setVertex(pos, color);
        setVertex(pos, color);
        //setVertex(pos, color);
        if (i == segments-1) {

            //setVertex(pos, color);
            setVertex(startpos, color);
            //setVertex(startpos, color);
            //setVertex(startpos, color);
            //setVertex(startpos, color);
        }
        //setVertex(pos, color);
    }
    if (centerShown)
    {
        setVertex(startpos, color);
        setVertex(centerPos, color);

    }
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

    glLineWidth(1.5f);
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
    if (angle == 0) {
        return pos;
    }
    glm::vec2 newPos;
    newPos.x = pos.x * cos(angle) - pos.y * sin(angle);
    newPos.y = pos.x * sin(angle) + pos.y * cos(angle);
    return newPos;
}

void ShapeRenderer::drawRect(glm::vec2 position, glm::vec2 size, glm::vec4 color) {
    //Topline
    drawLine(position, {position.x + size.x, position.y}, color);
    //Left side
    drawLine(position, {position.x, position.y + size.y}, color);
    //Botline
    drawLine({position.x, position.y + size.y }, {position.x + size.x, position.y + size.y}, color);
    // RightSide
    drawLine({position.x + size.x, position.y + size.y }, {position.x + size.x, position.y}, color);
}


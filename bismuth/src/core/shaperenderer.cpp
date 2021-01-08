#include "bismuth/primitives.hpp"
#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include <bismuth/shaperenderer.hpp>
#include <bismuth/logging.hpp>
#include <glad/glad.h>
#include <string>
#include <bismuth/iomanager.hpp>

using namespace bi;

ShapeRenderer::~ShapeRenderer() {
    bi::log("ShapeRenderer destroyed");
}

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

void ShapeRenderer::beginBatch() {
    renderData.currentLocationPtr = renderData.vertexBuffer;
}

void ShapeRenderer::endBatch() {
    GLsizeiptr size = (uint8_t*) this->renderData.currentLocationPtr - (uint8_t*) this->renderData.vertexBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, renderData.quadVB);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, renderData.vertexBuffer);


}

void ShapeRenderer::endFlushBegin() {
    endBatch();
    flush();
    beginBatch();
}
void ShapeRenderer::drawLine(glm::vec2 posFrom, glm::vec2 posTo, glm::vec4 color, float angle, bool centerShown) {
    checkVertexLimit();


    //finding center point
    //showing center
    //drawPolygon(center, 10, 6, {1,1,1,1}, angle, false);
    glm::vec2 center = (posFrom + posTo) * 0.5f;

    //using center to calculate new positions which are rotated
    glm::vec2 newFrom = rotatePoint(posFrom - center, angle);
    glm::vec2 newTo = rotatePoint(posTo - center, angle);

    if (angle == 0) {

        setVertex(posFrom, color);
        setVertex(posTo, color);
    }
    else {
        //displace with center so its not at origin {0,0}
        setVertex(newFrom + center, color);
        setVertex(newTo + center, color);

    }
    if (centerShown) {
        drawPoint((posFrom + posTo) * 0.5f);
    }
}

void ShapeRenderer::checkVertexLimit() {
    if (renderData.vertexCounter >= maxVertexCount) {
        endFlushBegin();
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

void ShapeRenderer::drawGrid(glm::vec2 tileSize, glm::vec2 windowSize, glm::vec2 offset, glm::vec4 color) {

    int xCount = windowSize.x / tileSize.x;
    int yCount = windowSize.y / tileSize.y;

    //vertical
    for (int i = 0; i <= xCount; i++) {
        drawLine({ i * tileSize.x + offset.x, offset.y }, { i * tileSize.x + offset.x, yCount * tileSize.y + offset.y }, color);
    }

    //horizontal
    for (int i = 0; i <= yCount; i++) {
        drawLine({ offset.x, i * tileSize.y + offset.y }, { xCount * tileSize.x + offset.x, i * tileSize.y + offset.y }, color);
    }

}

void ShapeRenderer::flush() {

    this->shader.use();

    shader.uploadUniformMat4("uMvp", camera.projectionMatrix * camera.viewMatrix);

    glBindVertexArray(renderData.quadVA);
    //enable position
    glEnableVertexAttribArray(0);
    //enable color
    glEnableVertexAttribArray(1);

    glLineWidth(1.2f);
    glDrawArrays(GL_LINES, 0, renderData.vertexCounter);
    //if Filled
    //glDrawArrays(GL_POLYGON, 0, renderData.vertexCounter);

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

void ShapeRenderer::drawRect(glm::vec2 position, glm::vec2 size, glm::vec4 color, float angle, bool centerShown) {


    if (angle == 0) {
        //Topline
        drawLine(position, {position.x + size.x, position.y}, color);
        //Left side
        drawLine(position, {position.x, position.y + size.y}, color);
        //Botline
        drawLine({position.x, position.y + size.y }, {position.x + size.x, position.y + size.y}, color);
        // RightSide
        drawLine({position.x + size.x, position.y + size.y }, {position.x + size.x, position.y}, color);
    }
    else {
        glm::vec2 halfDims(size * 0.5f);

        glm::vec2 tl(-halfDims.x, halfDims.y);
        glm::vec2 bl(-halfDims.x, -halfDims.y);
        glm::vec2 br(halfDims.x, -halfDims.y);
        glm::vec2 tr(halfDims.x, halfDims.y);

        glm::vec2 topLeft, botLeft, botRight, topRight;

        topLeft = rotatePoint(tl, angle) + halfDims + position;
        botLeft = rotatePoint(bl, angle) + halfDims + position;
        botRight = rotatePoint(br, angle) + halfDims + position;
        topRight = rotatePoint(tr, angle) + halfDims + position;
        drawLine(topLeft, topRight, color);
        drawLine(topLeft, botLeft, color);
        drawLine(botLeft, botRight, color);
        drawLine(botRight, topRight, color);

    }

    if (centerShown) {
        glm::vec2 center = (position + size * 0.5f);
        drawPoint((center));
    }
}

void ShapeRenderer::drawPoint(glm::vec2 point, float angle) {
    drawPolygon(point, 4, 8, {0,1,0,1}, angle);
}


#include "playersystem.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/mouselistener.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtx/string_cast.hpp"
#include <bismuth/particle.hpp>
#include <glad/glad.h>

PlayerSystem::PlayerSystem()
{
    drill.init();
}
PlayerSystem::~PlayerSystem() { }

void PlayerSystem::update(float dt, bi::TiledObject player, glm::vec2 mouse)
{
    accDt += dt;
    glm::vec2 currentTile = getCurrentTile(currentDir);

    if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_D) && !xAxisMoving()) {
        keyDown = true;
        newDirection = glm::vec2 { 1, 0 };
        //bi::log("adding right");
        directionQueue.push(newDirection);
        //bi::keyInput().donePressing(GLFW_KEY_D);

    }

    else if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_A) && !xAxisMoving()) {
        keyDown = true;
        newDirection = { -1, 0 };
        directionQueue.push(newDirection);
        bi::keyInput().donePressing(GLFW_KEY_A);
    }

    else if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_S) && !yAxisMoving()) {
        keyDown = true;
        newDirection = { 0, 1 };
        directionQueue.push(newDirection);
        if (currentDir == zero) {
            currentDir = newDirection;
            lastTile = lastTile + newDirection;
            drill.playAnimationLeft(dt, newPos);
            directionQueue.pop();
        }
        //bi::keyInput().donePressing(GLFW_KEY_S);
    }

    else if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_W) && !yAxisMoving()) {
        keyDown = true;
        newDirection = { 0, -1 };
        directionQueue.push(newDirection);
        bi::keyInput().donePressing(GLFW_KEY_W);
        //bi::log("adding up");
    } else if (bi::keyInput().isKeyPressedOnce(GLFW_KEY_SPACE)) {
        keyDown = true;
        newDirection = { 0, 0 };
        directionQueue.push(newDirection);
    }

    if (newPos == zero) {
        newPos = { 32, 32 };
        currentDir = { 1, 0 };
        lastTile = getCurrentTile(currentDir);
        if (lastTile.x == 2.0f && lastTile.y == 2.0f) {
            //bi::log("Last tile is {2.2}");
        } else {
            bi::log("Failed isnt as expected", glm::to_string(lastTile));
        }
    }

    newPos += currentDir * dt * speed;
    //
    currentTile = getCurrentTile(currentDir);

    if (currentDir == right) {
        currentAnimation = "right";
        if (newPos.x - 16 > (lastTile.x * 16.0f)) {
            newPos.x = (currentTile.x) * 16.0f;
            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();
                directionQueue.pop();
                //showDirection();
            }
            lastTile = currentTile;
        }

    } else if (currentDir == left) {
        // fix y axis
        currentAnimation = "left";
        if (newPos.x + 16 < (lastTile.x * 16.0f)) {

            newPos.x = (currentTile.x) * 16.0f;
            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();
                directionQueue.pop();
                //showDirection();
            }
            lastTile = currentTile;
        }
    }

    else if (currentDir == up) {
        currentAnimation = "up";
        if (newPos.y + 16 < (lastTile.y * 16.0f)) {
            newPos.y = (currentTile.y) * 16.0f;
            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();
                directionQueue.pop();
                //showDirection();
            }
            lastTile = currentTile;
        }
    }

    else if (currentDir == down) {
        currentAnimation = "down";
        if (newPos.y - 16 > (lastTile.y * 16.0f)) {

            //bi::log("reached down");
            newPos.y = (currentTile.y) * 16.0f;
            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();
                directionQueue.pop();
                //showDirection();
            }

            lastTile = currentTile;
        }
    }
    //player.tile.setPosition(newPos);

    drill.playAnimation(dt, currentAnimation, newPos);
    bi::ioManager().renderer->endFlushBegin();
    //bi::ioManager().renderer->drawTile(player.tile, { 1, 1, 1, 1 });
    bi::ioManager().renderer->setAdditiveBlend();
    dustTrail.update(dt, { newPos.x, newPos.y }, currentDir);
    bi::ioManager().renderer->endFlushBegin();
    //bi::ioManager().renderer->setDefaultBlend();


    //if (currentDir == zero) {
        //particleemitter.setLife(0.0f);
    //} else
        //particleemitter.setLife(1.0f);

    //particleemitter.emit(dt, { newPos.x, newPos.y }, currentDir, { 100.0f, 100.0f }, { 0.1f, 0.2f, 0.5f, 0.5f }, smokeTexId, 1, { 16.0f, 16.0f }, { 10, 10 }, true);
    //shaperenderer.drawRect(newPos, {player.tile.getTileSize().x, player.tile.getTileSize().y} , {1,0,0,1});

    //drawDirection(shaperenderer);
}

void PlayerSystem::drawLeft(bi::ShapeRenderer& shaperenderer)
{
    shaperenderer.drawLine({ newPos.x, newPos.y }, { newPos.x, newPos.y + 16 }, { 0, 1, 0, 1 });
}

void PlayerSystem::drawRight(bi::ShapeRenderer& shaperenderer)
{

    shaperenderer.drawLine({ newPos.x + 16, newPos.y }, { newPos.x + 16, newPos.y + 16 }, { 0, 1, 0, 1 });
}

void PlayerSystem::drawUp(bi::ShapeRenderer& shaperenderer)
{
    shaperenderer.drawLine({ newPos.x, newPos.y }, { newPos.x + 16, newPos.y }, { 0, 1, 0, 1 });
}

void PlayerSystem::drawDown(bi::ShapeRenderer& shaperenderer)
{
    shaperenderer.drawLine({ newPos.x, newPos.y + 16 }, { newPos.x + 16, newPos.y + 16 }, { 0, 1, 0, 1 });
}

void PlayerSystem::drawDirection(bi::ShapeRenderer& shaperenderer)
{

    if (newDirection == left) {
        drawLeft(shaperenderer);
    } else if (newDirection == right) {
        drawRight(shaperenderer);
    } else if (newDirection == up) {
        drawUp(shaperenderer);
    } else if (newDirection == down) {
        drawDown(shaperenderer);
    }
}
glm::vec2 PlayerSystem::setNextTile(glm::vec2 point)
{
    //lastTile = getCurrentTile(point);
    //nextTile.y = std::max(nextTile.y, 0.0f);
    //nextTile.x = std::max(nextTile.x, 0.0f);
    int currentx = (int)(newPos.x + (16.0f / 2.0f)) / 16.0f;
    int currenty = (int)(newPos.y + (16.0f / 2.0f)) / 16.0f;
    lastTile = { currentx, currenty };

    return lastTile;
}

glm::vec2 PlayerSystem::getCurrentTile(glm::vec2 dir)
{
    glm::vec2 tileSize { 16.0f, 16.0f };

    int currentx = 0;
    int currenty = 0;
    if (dir == up) {
        currentx = (int)(newPos.x) / tileSize.x;
        //currenty  = (int) (newPos.y + tileSize.y) / tileSize.y;
        currenty = (int)(newPos.y) / tileSize.y;
    }

    if (dir == down) {
        currentx = (int)(newPos.x) / tileSize.x;
        currenty = (int)(newPos.y + tileSize.y) / tileSize.y;
    }

    if (dir == left) {
        currentx = (int)(newPos.x) / tileSize.x;
        currenty = (int)(newPos.y) / tileSize.y;
    }

    if (dir == right) {
        currentx = (int)(newPos.x + tileSize.x) / tileSize.x;
        currenty = (int)(newPos.y) / tileSize.y;
    }

    currentTile = { currentx, currenty };
    //bi::log("currentTile" ,glm::to_string(currentTile));
    //currentTile = newPos) / tileSize * 16.0f;

    currentx = (int)(newPos.x + (tileSize.x / 2.0f)) / tileSize.x;
    currenty = (int)(newPos.y + (tileSize.y / 2.0f)) / tileSize.y;

    currentTile = { currentx, currenty };

    return currentTile;
}

bool PlayerSystem::xAxisMoving()
{
    return newDirection == left || newDirection == right;
    //return newDirection == left || newDirection == right || currentDir == left || currentDir == right;
}

bool PlayerSystem::yAxisMoving()
{
    return newDirection == up || newDirection == down;
    //return newDirection == up || newDirection == down || currentDir == down || currentDir == up;
}
void PlayerSystem::showDirection()
{
    if (currentDir == right) {
        bi::log("playing right");
    }

    else if (currentDir == left) {

        bi::log("playing left");
    }

    else if (currentDir == up) {

        bi::log("playing up");
    }

    else if (currentDir == down) {

        bi::log("playing down");
    }
}

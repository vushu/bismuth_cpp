#include "playersystem.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/mouselistener.hpp"
#include "glm/fwd.hpp"
#include "glm/gtx/string_cast.hpp"

PlayerSystem::PlayerSystem() {}
PlayerSystem::~PlayerSystem() {}

void PlayerSystem::update(float dt, bi::TiledObject player, bi::Renderer &renderer, bi::ShapeRenderer& shaperenderer, glm::vec2 mouse) {

    if (bi::keyInput().isKeyPressed(GLFW_KEY_D) && currentDir != left) {
        newDirection = glm::vec2 {1, 0};
        directionQueue.push(newDirection);
        setNextTile();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_A) && currentDir != right) {
        newDirection = {-1,0};
        directionQueue.push(newDirection);
        setNextTile();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_S) && currentDir != up) {
        newDirection = {0, 1} ;
        directionQueue.push(newDirection);
        setNextTile();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_W) && currentDir != down) {
        newDirection = { 0,-1 };
        directionQueue.push(newDirection);
        setNextTile();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_SPACE)) {
        newDirection = { 0, 0 };
        directionQueue.push(newDirection);
        setNextTile();
    }
    if (newPos == glm::zero<glm::vec2>()) {
        //newPos = {1,1};
        currentDir = {1,0};
        newPos = {0,0};
    }

    //direction = currentDir * dt * speed;

    //if (currentDir == left){
    //newPos.y = (getCurrentTile(left).y * 16);
    //bi::log("new pos y", newPos.y);
    //}
    //if (currentDir == right){
    //newPos.y = getCurrentTile(right).y * 16;
    //}
    //if (currentDir == up) {
    //newPos.x = getCurrentTile(up).x * 16;
    //}

    //if (currentDir == down) {
    //newPos.x = getCurrentTile(down).x * 16;
    //}
    newPos += currentDir * dt * speed;
    player.tile.setPosition(newPos);
    glm::vec2 curdir = getCurrentTile(currentDir);


    if ((curdir.x == nextTile.x && curdir.y == nextTile.y)){
        bi::log("curdir:", glm::to_string(curdir));
        //newPos = getCurrentTile(currentDir) * 16;
        currentDir = newDirection;
    }


    renderer.drawTile(player.tile, {1,1,1,1});


    shaperenderer.drawRect(newPos, {player.tile.getTileSize().x, player.tile.getTileSize().y} , {1,0,0,1});

    drawDirection(shaperenderer);

}

void PlayerSystem::drawLeft(bi::ShapeRenderer& shaperenderer) {

    shaperenderer.drawLine({newPos.x, newPos.y}, {newPos.x, newPos.y+16}, {0,1,0,1});
}

void PlayerSystem::drawRight(bi::ShapeRenderer& shaperenderer) {

    shaperenderer.drawLine({newPos.x + 16, newPos.y}, {newPos.x + 16, newPos.y + 16 }, {0,1,0,1});
}

void PlayerSystem::drawUp(bi::ShapeRenderer& shaperenderer) {
    shaperenderer.drawLine({newPos.x, newPos.y}, {newPos.x + 16, newPos.y}, {0,1,0,1});
}

void PlayerSystem::drawDown(bi::ShapeRenderer& shaperenderer) {
    shaperenderer.drawLine({newPos.x, newPos.y + 16}, { newPos.x + 16, newPos.y + 16}, {0,1,0,1});
}

void PlayerSystem::drawDirection(bi::ShapeRenderer& shaperenderer) {

    if (newDirection == left) {
        drawLeft(shaperenderer);
    }
    else if (newDirection == right) {
        drawRight(shaperenderer);
    }
    else if (newDirection == up) {
        drawUp(shaperenderer);
    }
    else if (newDirection == down) {
        drawDown(shaperenderer);
    }
}
glm::vec2 PlayerSystem::setNextTile() {
    nextTile = getCurrentTile(currentDir) + currentDir;
    //nextTile.y = std::max(nextTile.y, 0.0f);
    //nextTile.x = std::max(nextTile.x, 0.0f);


    return nextTile;
}

glm::vec2 PlayerSystem::getCurrentTile(glm::vec2 dir) {
    glm::vec2 tileSize{16.0f,16.0f};

    int currentx  = 0;
    int currenty  = 0;
    if (dir == up) {
        currentx  = (int) (newPos.x) / tileSize.x;
        currenty  = (int) (newPos.y + tileSize.y) / tileSize.y;
    }

    if (dir == down) {
        currentx  = (int) (newPos.x) / tileSize.x;
        currenty  = (int) (newPos.y) / tileSize.y;
    }

    if (dir == left) {
        currentx  = (int) (newPos.x + tileSize.x) / tileSize.x;
        currenty  = (int) (newPos.y) / tileSize.y;
    }

    if (dir == right) {
        currentx  = (int) (newPos.x + tileSize.x) / tileSize.x;
        currenty  = (int) (newPos.y) / tileSize.y;
    }

    currentTile = { currentx, currenty };
    //bi::log("currentTile" ,glm::to_string(currentTile));
    //currentTile = newPos) / tileSize * 16.0f;

    return currentTile;
}

/*
   glm::vec2 PlayerSystem::getCurrentTile() {
// need to consider direction to collide on tile
float currentx  = (int) (newPos.x + 16 * newDirection.x) / 16;
float currenty  = (int) (newPos.y + 16 * newDirection.y) / 16;
currentTile = {currentx, currenty};
return currentTile;
}
*/

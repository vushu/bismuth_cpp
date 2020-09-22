#include "playersystem.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/mouselistener.hpp"
#include "glm/fwd.hpp"
#include "glm/gtx/string_cast.hpp"

PlayerSystem::PlayerSystem() {}
PlayerSystem::~PlayerSystem() {}

void PlayerSystem::update(float dt, bi::TiledObject player, bi::Renderer &renderer, bi::ShapeRenderer& shaperenderer, glm::vec2 mouse) {
    glm::vec2 currentTile = getCurrentTile(currentDir);

    bi::log("current tile", glm::to_string(currentTile));
    //if (((int)newPos.x - 8) % 8 == 0 && ((int) (newPos.y - 8)) % 8 == 0) {
    if (bi::keyInput().isKeyPressed(GLFW_KEY_D)  && !moving && !xAxisMoving()) {
        newDirection = glm::vec2 {1, 0};
        currentDir = newDirection;
        directionQueue.push(newDirection);
        setNextTile(currentDir);
        moving = true;
    }

    else if (bi::keyInput().isKeyPressed(GLFW_KEY_A) && !moving && !xAxisMoving()) {
        newDirection = {-1,0};
        currentDir = newDirection;
        directionQueue.push(newDirection);
        setNextTile(currentDir);
        moving = true;
    }

    else if (bi::keyInput().isKeyPressed(GLFW_KEY_S) && !yAxisMoving() && !moving) {
        newDirection = {0, 1} ;
        currentDir = newDirection;
        directionQueue.push(newDirection);
        setNextTile(currentDir);
        moving = true;
    }

    else if (bi::keyInput().isKeyPressed(GLFW_KEY_W) && !yAxisMoving() && !moving) {
        newDirection = { 0,-1 };
        currentDir = newDirection;
        directionQueue.push(newDirection);
        setNextTile(currentDir);
        moving = true;
    }
    else if (bi::keyInput().isKeyPressed(GLFW_KEY_SPACE)) {
        newDirection = { 0, 0 };
        currentDir = newDirection;
        directionQueue.push(newDirection);
        //setNextTile();
    }
    //}

    if (newPos == glm::zero<glm::vec2>()) {
        //newPos = player.tile.getPosition();
        newPos = {32,32};
        currentDir = {1,0};
        lastTile = getCurrentTile(currentDir);
        if (lastTile.x == 2.0f && lastTile.y == 2.0f) {
            bi::log("Last tile is {2.2}");
        }
        else {
            bi::log("Failed isnt as expected", glm::to_string(lastTile));
        }

        //
    }
    newPos += currentDir * dt * speed;
    //
    currentTile = getCurrentTile(currentDir);


    if (currentDir == right) {
        //newPos.y -= 8;
        //currentTile = getCurrentTile(left);
        bi::log("right x", newPos.x);
        bi::log("last tile", lastTile.x * 16.0f);
        if (newPos.x - 16 > (lastTile.x * 16.0f)) {
            newPos.x =  (currentTile.x) * 16.0f;
            moving = false;
        }

    }
    else if (currentDir == left) {
        // fix y axis
        if (newPos.x + 16 < (lastTile.x * 16.0f)) {
            newPos.x = (currentTile.x) * 16.0f;
            //lastTile = currentTile + currentDir;
            moving = false;
        }
    }

    else if (currentDir == up) {

        //lastTile.y -= 1;
        if (newPos.y + 16 < (lastTile.y * 16.0f)) {
            newPos.y = (currentTile.y) * 16.0f;
            //currentDir = {0,0};
            moving = false;
        }
    }
    else if (currentDir == down) {

        if (newPos.y - 16 > (lastTile.y * 16.0f)) {
            newPos.y = (currentTile.y) * 16.0f;
            moving = false;
            //currentDir = {0,0};
        }

    }

    //lastTile = currentTile + currentDir;

    player.tile.setPosition(newPos);


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
glm::vec2 PlayerSystem::setNextTile(glm::vec2 point) {
    //lastTile = getCurrentTile(point);
    //nextTile.y = std::max(nextTile.y, 0.0f);
    //nextTile.x = std::max(nextTile.x, 0.0f);
    int currentx  = (int) (newPos.x + (16.0f/2.0f)) / 16.0f;
    int currenty  = (int) (newPos.y + (16.0f/2.0f)) / 16.0f;
    lastTile = { currentx, currenty };


    return lastTile;
}

glm::vec2 PlayerSystem::getCurrentTile(glm::vec2 dir) {
    glm::vec2 tileSize{16.0f,16.0f};

    int currentx  = 0;
    int currenty  = 0;
    if (dir == up) {
        currentx  = (int) (newPos.x) / tileSize.x;
        //currenty  = (int) (newPos.y + tileSize.y) / tileSize.y;
        currenty  = (int) (newPos.y) / tileSize.y;

    }

    if (dir == down) {
        currentx  = (int) (newPos.x) / tileSize.x;
        currenty  = (int) (newPos.y + tileSize.y) / tileSize.y;
    }

    if (dir == left) {
        currentx  = (int) (newPos.x) / tileSize.x;
        currenty  = (int) (newPos.y) / tileSize.y;
    }

    if (dir == right) {
        currentx  = (int) (newPos.x + tileSize.x) / tileSize.x;
        currenty  = (int) (newPos.y) / tileSize.y;
    }

    currentTile = { currentx, currenty };
    //bi::log("currentTile" ,glm::to_string(currentTile));
    //currentTile = newPos) / tileSize * 16.0f;


    currentx  = (int) (newPos.x + (tileSize.x/2.0f)) / tileSize.x;
    currenty  = (int) (newPos.y + (tileSize.y/2.0f)) / tileSize.y;
    currentTile = { currentx, currenty };
    return currentTile;
}

bool PlayerSystem::xAxisMoving() {
    return currentDir == left || currentDir == right;
}

bool PlayerSystem::yAxisMoving() {
    return currentDir == up || currentDir == down;
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

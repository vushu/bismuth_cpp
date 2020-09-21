#include "playersystem.hpp"
#include "bismuth/mouselistener.hpp"
#include "glm/fwd.hpp"

PlayerSystem::PlayerSystem() {}
PlayerSystem::~PlayerSystem() {}

void PlayerSystem::update(float dt, bi::TiledObject player, bi::Renderer &renderer, bi::ShapeRenderer& shaperenderer, glm::vec2 mouse) {

    if (bi::keyInput().isKeyPressed(GLFW_KEY_D)) {
        direction = glm::vec2{1, 0};
        directionQueue.push(direction);
        setNextTile();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_A)) {
        direction = {-1,0};
        directionQueue.push(direction);
        setNextTile();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_S)) {
        direction = {0, 1} ;
        directionQueue.push(direction);
        setNextTile();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_W)) {
        direction = { 0,-1 };
        directionQueue.push(direction);
        setNextTile();
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_SPACE)) {
        direction = { 0, 0 };
        directionQueue.push(direction);
    }
    if (newPos == glm::zero<glm::vec2>()) {
        newPos = player.tile.getPosition();
        currentDir = {1,0};
        //newPos = {0,0};
    }



    //direction = currentDir * dt * speed;
    newPos += currentDir * dt * speed;


    //int currentx  = (int) ((30 * 16) / (newPos.x));
    //

    player.tile.setPosition(newPos);
    if (getCurrentTile() == nextTile){
        if (!directionQueue.empty()) {
            currentDir = directionQueue.front();
            directionQueue.pop();
            //newPos += dir * dt * speed;
        }
    }


    renderer.drawTile(player.tile, {1,1,1,1});

    shaperenderer.drawRect(newPos, {player.tile.getTileSize().x, player.tile.getTileSize().y} , {1,0,0,1});
    shaperenderer.drawLine({newPos.x + 16 * currentDir.x, newPos.y * 16 * currentDir.y}, {newPos.x + 16 *currentDir.x, newPos.y + 16 * currentDir.y}, {0,1,0,1});

}

void PlayerSystem::drawLeft() {

}

void PlayerSystem::drawRight() {

}

void PlayerSystem::drawUp() {

}

void PlayerSystem::drawDown() {

}
glm::vec2 PlayerSystem::setNextTile() {
    nextTile = getCurrentTile() + currentDir;
    return nextTile;
}

glm::vec2 PlayerSystem::getCurrentTile() {
    // need to consider direction to collide on tile
    float currentx  = (int) (newPos.x + 16 * currentDir.x) / 16;
    float currenty  = (int) (newPos.y + 16 * currentDir.y) / 16;
    currentTile = {currentx, currenty};
    return currentTile;
}

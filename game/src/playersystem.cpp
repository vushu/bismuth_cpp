#include "playersystem.hpp"
#include "bismuth/mouselistener.hpp"

PlayerSystem::PlayerSystem() {}
PlayerSystem::~PlayerSystem() {}

void PlayerSystem::update(float dt, bi::TiledObject player, bi::Renderer &renderer, bi::ShapeRenderer& shaperenderer, glm::vec2 mouse) {

    if (bi::keyInput().isKeyPressed(GLFW_KEY_D)) {
        direction = glm::vec2{1, 0};
        directionQueue.push_back(direction);
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_A)) {
        direction = {-1,0};
        directionQueue.push_back(direction);
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_S)) {
        direction = {0, 1} ;
        directionQueue.push_back(direction);
        hit = true;
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_W)) {
        direction = { 0,-1 };
        directionQueue.push_back(direction);
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_SPACE)) {
        direction = { 0, 0 };
        directionQueue.push_back(direction);
    }
    if (newPos == glm::zero<glm::vec2>()) {
        //newPos = player.tile.getPosition();
        newPos = {0,0};
    }

    //glm::vec2 dir = directionQueue.back();
    //directionQueue.pop_back();
    //direction = direction * dt * speed;
    newPos += direction * dt * speed;


    //int currentx  = (int) ((30 * 16) / (newPos.x));
    float currentx  = (int) (newPos.x + 12) / 16;
    float currenty  = (int) (newPos.y + 12) / 16;
    //int currenty  = (int) (newPos.y + 8) / 17 * 16;

    bi::log("tilePosX: ", currentx);
    bi::log("tilePosY: ", currenty);
    //
    player.tile.setPosition(newPos);

    renderer.drawTile(player.tile, {1,1,1,1});
    shaperenderer.drawRect(newPos, {player.tile.getTileSize().x, player.tile.getTileSize().y} , {1,0,0,1});
    shaperenderer.drawLine({newPos.x + 12, newPos.y}, {newPos.x + 12, newPos.y + 16}, {0,1,0,1});

}

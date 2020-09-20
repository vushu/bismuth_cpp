#include "playersystem.hpp"

PlayerSystem::PlayerSystem() {}
PlayerSystem::~PlayerSystem() {}

void PlayerSystem::update(float dt, bi::TiledObject player, bi::Renderer &renderer, bi::ShapeRenderer& shaperenderer) {

    if (bi::keyInput().isKeyPressed(GLFW_KEY_D)) {
        direction = glm::vec2{1, 0};
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_A)) {
        direction = {-1,0};
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_S)) {
        direction = {0, 1} ;
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_W)) {
        direction = { 0,-1 };
    }

    if (newPos == glm::zero<glm::vec2>()) {
        newPos = player.tile.getPosition();
    }

    //direction = direction * dt * speed;
    newPos += direction * dt * speed;
    int currentx  = (int) (newPos.x + 8)/30;
    int currenty  = (int) (newPos.y + 8)/17;
    //bi::log("tilePosX: ", currentx);
    //bi::log("tilePosY: ", currenty);
    player.tile.setPosition(newPos);

    renderer.drawTile(player.tile, {1,1,1,1});
    shaperenderer.drawRect(newPos, {16,16}, {1,0,0,1});

}

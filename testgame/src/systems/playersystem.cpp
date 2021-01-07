#include "playersystem.hpp"
#include "bismuth/font.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include <bismuth/particle.hpp>
#include <string>

PlayerSystem::PlayerSystem() {
    drill.init();
}

PlayerSystem::~PlayerSystem() {}

void PlayerSystem::handleInput(float dt) {

    inputHandleDirection({1, 0}, GLFW_KEY_RIGHT);
    inputHandleDirection({1, 0}, GLFW_KEY_D);
    inputHandleDirection({-1, 0}, GLFW_KEY_LEFT);
    inputHandleDirection({-1, 0}, GLFW_KEY_A);
    inputHandleDirection({0, -1}, GLFW_KEY_UP);
    inputHandleDirection({0, -1}, GLFW_KEY_W);
    inputHandleDirection({0, 1}, GLFW_KEY_DOWN);
    inputHandleDirection({0, 1}, GLFW_KEY_S);
}

void PlayerSystem::snapToGrid() {
    if (currentDir == zero) {
        //bi::log("waiting");
        //drill.setLastTile();
    } else if (currentDir == right) {
        currentAnimation = "right";
        // if left side reached end of last tile
        if (newPos.x >= (currentTile.x * 16.0f) + 16.0f) {

            // snap to grid, to ensure correct behavior
            newPos.x = currentTile.x * 16.0f + 16.0f;
            bi::log("Drill snap right to grid");

            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();
                directionQueue.pop();
                //showDirection();
            }
            currentTile += currentDir;
            //drill.setLastTile();
        }

    } else if (currentDir == left) {
        currentAnimation = "left";
        if (newPos.x < 0) {
            newPos.x = 0;
        }
            // if left side reached end of last tile
        else if (newPos.x + 16.0f <= (currentTile.x * 16.0f)) {

            // snap to grid, to ensure correct behavior
            newPos.x = currentTile.x * 16.0f - 16.0f;
            bi::log("Drill snap left to grid");

            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();
                directionQueue.pop();
                //showDirection();
            }
            currentTile += currentDir;
            //drill.setLastTile();
        }

    } else if (currentDir == up) {
        currentAnimation = "up";
        if (newPos.y < 0) {
            bi::log("hitting roof");
            newPos.y = 0;
        }
            // if left side reached end of last tile
        else if (newPos.y + 16.0f <= currentTile.y * 16.0f) {
            // snap to grid, to ensure correct behavior
            newPos.y = currentTile.y * 16.0f - 16.0f;
            bi::log("Drill snap up to grid");

            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();
                directionQueue.pop();
                //showDirection();
            }
            currentTile += currentDir;
            //drill.setLastTile();
        }
    } else if (currentDir == down) {
        currentAnimation = "down";
        if (newPos.y >= currentTile.y * 16.0f + 16.0f) {
            // snap to grid, to ensure correct behavior
            newPos.y = currentTile.y * 16.0f + 16.0f;
            bi::log("Drill snap down to grid");

            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();
                directionQueue.pop();
                //showDirection();
            }
            currentTile += currentDir;
            //drill.setLastTile();
        }
    }
}

void PlayerSystem::snapToGrid2() {
    if (currentDir == zero) {
        //bi::log("waiting");
        //drill.setLastTile();
    } else if (currentDir == right) {
        currentAnimation = "right";
        // if left side reached end of last tile
        if (newPos.x - 16 > (lastTile.x * 16.0f)) {

            // snap to grid, to ensure correct behavior
            newPos.x = (currentTile.x) * 16.0f;
            //bi::log("Drill snap to grid");

            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();
                directionQueue.pop();
                //showDirection();
            }
            drill.setLastTile();
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
            drill.setLastTile();
            lastTile = currentTile;
        }
    } else if (currentDir == up) {
        currentAnimation = "up";
        if (newPos.y + 16 < (lastTile.y * 16.0f)) {
            newPos.y = (currentTile.y) * 16.0f;
            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();

                directionQueue.pop();
                //                showDirection();
            }

            drill.setLastTile();
            lastTile = currentTile;
        }
    } else if (currentDir == down) {
        currentAnimation = "down";
        if (newPos.y - 16 > (lastTile.y * 16.0f)) {

            //bi::log("reached down");
            newPos.y = (currentTile.y) * 16.0f;
            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();
                directionQueue.pop();
                //showDirection();
            }

            drill.setLastTile();
            lastTile = currentTile;
        }
    }
}


bool PlayerSystem::snapToGrid(glm::vec2 position, glm::vec2 direction) {

    glm::vec2 currentTileAtDirection = drill.getCurrentTile(position, direction);
    glm::vec2 lastTilePos = lastTile * 16.0f;
    glm::vec2 currentTileAtDirectionPos = currentTileAtDirection * 16.0f;
    bool snapped = false;

    if (direction == right) {
        if (position.x - 16.0f > lastTilePos.x) {
            position.x = currentTileAtDirectionPos.x;
            snapped = true;
        }
    } else if (direction == left) {
        if (position.x + 16.0f < lastTilePos.x) {
            position.x = currentTileAtDirectionPos.x;
            snapped = true;
        }
    } else if (direction == up) {

        if (position.y + 16.0f < lastTilePos.y) {
            position.y = currentTileAtDirectionPos.y;
            snapped = true;
        }
    } else if (direction == down) {
        if (position.y - 16.0f > lastTilePos.y) {
            position.y = currentTileAtDirectionPos.y;
            snapped = true;
        }
    }
    return snapped;
}

void PlayerSystem::update(float dt, glm::vec2 mouse, std::vector<bi::TiledObject> &objects, bi::Font &font) {
    updateSpeed();
    accDt += dt;
    //currentTile = drill.getCurrentTile(newPos, currentDir);

    if (newPos == zero) {
        newPos = {0, 3 * 16};
        currentDir = {1, 0};
        currentTile = {0, 3};
        lastTile = currentTile;
        drill.setLastTile();
    }
    newPos += currentDir * speed;
    currentTile = drill.getCurrentTile(newPos, currentDir);

    snapToGrid2();

//    bi::log("speed:", speed);
//    bi::log("position:", newPos);
//    bi::log("direction:", currentDir);

    handleCollision(objects, font);
    if (drill.drillNode != nullptr) {
      glm::vec2 drillTile = drill.getCurrentTile(drill.drillNode->position, drill.drillNode->direction);
        //glm::vec2 drillTile = setNextTile(currentTile, currentDir);
        if (currentTile == (drillTile + currentDir)) {
        } else if (currentTile != (drillTile + drill.drillNode->direction)) {
            bi::log("something went terribly wrong");
        }
    }

    drill.update(dt, currentDir, speed, newPos);
}

void PlayerSystem::updateSpeed() {
    if (newSpeed != 0) {
        speed += newSpeed;
        newSpeed = 0;
        bi::log("updating speed to:", speed);
    }
    if (speed > maxSpeed) {
        speed = maxSpeed;
        bi::log("Max speed reached set to ", speed);
    }
}

void PlayerSystem::handleCollision(std::vector<bi::TiledObject> &objects, bi::Font &font) {
    for (auto &object : objects) {
        glm::vec2 tilepos = {(object.object.getPosition().x) / 16.0f, (object.object.getPosition().y - 16) / 16.0f};
        /*
        if (object.object.getName() == "Rock") {
            if (tilepos == currentTile) {
                //bi::ioManager().renderer->drawText("GAME OVER: ", {40, 15}, font, {0.8f, 0.7f, 0.4f, 0.98f}, 1.0f);
                newPos = {0, 0};
                lastTile = {0, 0};
                currentDir = {1, 0};
                while (!directionQueue.empty()) {
                    directionQueue.pop();
                 else if (currentDir == right) {
        currentAnimation = "right";
        // if left side reached end of last tile
        if (newPos.x > (std::max(currentTile.x * 16.0f, 16.0f))) {

            // snap to grid, to ensure correct behavior
            newPos.x = std::max(currentTile.x * 16.0f, 16.0f);
            //bi::log("Drill snap to grid");

            if (!directionQueue.empty()) {
                currentDir = directionQueue.front();
                directionQueue.pop();
                //showDirection();
            }
            drill.setLastTile();
            currentTile += currentDir;
        }

    }
            }
        }
         */
        if (object.object.getName() == "Goal") {
            if (tilepos == currentTile) {
//                bi::ioManager().renderer->drawText("YOU WIN EM!", {50, 20}, font, {0.8f, 0.7f, 0.4f, 0.98f}, 1.0f);
                newPos = tilepos;
            }

        } else if (object.object.getName() == "Crystal") {
            //object.object.getPoints
            //glm::vec2 tilepos = {(object.object.getPosition().x) / 16.0f, (object.object.getPosition().y - 16) / 16.0f};
            //            glm::vec2 cT = drill.getCurrentTile(drill.drillNode->position, drill.drillNode->direction);
            //glm::vec2 cT = getCurrentTile(currentDir);
            //since tiled is anchored bottom left corner we with tilesize
            if (tilepos == currentTile) {

                if (object.getCustomProperty("harvested").exists()) {
                    if (!object.getCustomProperty("harvested").getBoolValue()) {
                        this->crystals++;
                        //TODO: HERE
                        //more than one cart will screw carts up

                        //Speed change will screw the carts up
                        this->drill.tailLength += 1;
                        //this->newSpeed += 0.1f;

                        if (object.setCustomProperty("harvested", true)) {
                            bi::log("Now harvested");
                        }
                    }
                }
            }
        }
    }
}

void PlayerSystem::drawLeft(bi::ShapeRenderer &shaperenderer) {
    shaperenderer.drawLine({newPos.x, newPos.y}, {newPos.x, newPos.y + 16}, {0, 1, 0, 1});
}

void PlayerSystem::drawRight(bi::ShapeRenderer &shaperenderer) {

    shaperenderer.drawLine({newPos.x + 16, newPos.y}, {newPos.x + 16, newPos.y + 16}, {0, 1, 0, 1});
}

void PlayerSystem::drawUp(bi::ShapeRenderer &shaperenderer) {
    shaperenderer.drawLine({newPos.x, newPos.y}, {newPos.x + 16, newPos.y}, {0, 1, 0, 1});
}

void PlayerSystem::drawDown(bi::ShapeRenderer &shaperenderer) {
    shaperenderer.drawLine({newPos.x, newPos.y + 16}, {newPos.x + 16, newPos.y + 16}, {0, 1, 0, 1});
}

void PlayerSystem::drawDirection(bi::ShapeRenderer &shaperenderer) {
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

glm::vec2 PlayerSystem::setNextTile(glm::vec2 currentTile, glm::vec2 direction) {
    if (direction == right) {
        currentTile.x = (int) (newPos.x / 16.0f);
    } else if (direction == left) {
        currentTile.x = (int) (newPos.x / 16.0f);
    } else if (direction == up) {
        currentTile.y = (int) (newPos.y / 16.0f);
    } else if (direction == down) {
        currentTile.y = (int) (newPos.y / 16.0f);
    }
    return currentTile;
}

glm::vec2 PlayerSystem::getCurrentTile(glm::vec2 dir) {
    glm::vec2 tileSize{16.0f, 16.0f};

    int currentx = 0;
    int currenty = 0;

    currentx = static_cast<int> (newPos.x + (tileSize.x * .5f)) / tileSize.x;
    currenty = static_cast<int> (newPos.y + (tileSize.y * .5f)) / tileSize.y;

    currentTile = {currentx, currenty};

    return currentTile;
}

bool PlayerSystem::xAxisMoving() {
    return newDirection == left || newDirection == right;
}

bool PlayerSystem::yAxisMoving() {
    return newDirection == up || newDirection == down;
}

void PlayerSystem::showDirection() {
    if (currentDir == right) {
        bi::log("playing right");
    } else if (currentDir == left) {

        bi::log("playing left");
    } else if (currentDir == up) {

        bi::log("playing up");
    } else if (currentDir == down) {
        bi::log("playing down");
    }
}

void PlayerSystem::inputHandleDirection(glm::vec2 direction, int key) {
    if (direction == right && !xAxisMoving() && bi::keyInput().isKeyPressedOnce(key)) {
        keyDown = true;
        newDirection = direction;
        directionQueue.push(direction);
    } else if (direction == left && !xAxisMoving() && bi::keyInput().isKeyPressedOnce(key)) {
        keyDown = true;
        newDirection = direction;
        directionQueue.push(direction);
    } else if (direction == up && !yAxisMoving() && bi::keyInput().isKeyPressedOnce(key)) {
        keyDown = true;
        newDirection = direction;
        directionQueue.push(direction);
    } else if (direction == down && !yAxisMoving() && bi::keyInput().isKeyPressedOnce(key)) {
        keyDown = true;
        newDirection = direction;
        directionQueue.push(direction);
    }
}

void PlayerSystem::draw(float dt) {
    drill.draw();
    drill.playAnimationByDirection(dt, currentDir, newPos);
    //bi::ioManager().renderer->drawTile(player.tile, { 1, 1, 1, 1 });
    accDt = 0.0f;
    bi::ioManager().renderer->endFlushBegin();
}

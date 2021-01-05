#include "drill.hpp"
#include "bismuth/logging.hpp"
#include <bismuth/animatedsprite.hpp>
#include <bismuth/iomanager.hpp>
#include <bismuth/math.hpp>

Drill::~Drill() {
    Node *lastNode;
    Node *current = drillNode;
    while (current) {
        lastNode = current;
        current = current->next;
        delete lastNode;
    }
}

Drill::Drill() {}

void Drill::setLastTile() {
    //looping through all nodes and set their last tile
    if (tailLength == 0)
        return;
    Node *parent = drillNode;
    while (parent) {

        parent->lastTile = getCurrentTile(parent->position, parent->direction);
        if (parent->next) {
            parent->next->nextDirection = parent->direction;
        }
        parent = parent->next;
    }
}

bool Drill::snapToGrid(Node *cart) {

    glm::vec2 direction = cart->direction;
    glm::vec2 currentTileAtDirection = getCurrentTile(cart->position, direction);
    glm::vec2 lastTilePos = cart->lastTile * 16.0f;
    glm::vec2 currentTileAtDirectionPos = currentTileAtDirection * 16.0f;
    bool snapped = false;

    if (direction == right) {
        if (cart->position.x - 16.0f > lastTilePos.x) {
            cart->position.x = currentTileAtDirectionPos.x;
            snapped = true;
        }
    } else if (direction == left) {
        if (cart->position.x + 16.0f < lastTilePos.x) {
            cart->position.x = currentTileAtDirectionPos.x;
            snapped = true;
        }
    } else if (direction == up) {

        if (cart->position.y + 16.0f < lastTilePos.y) {
            cart->position.y = currentTileAtDirectionPos.y;
            snapped = true;
        }
    } else if (direction == down) {
        if (cart->position.y - 16.0f > lastTilePos.y) {
            cart->position.y = currentTileAtDirectionPos.y;
            snapped = true;
        }
    }

    if (snapped) {
        //cart->lastTile = getCurrentTile(cart->position, cart->direction);
        if (cart->next)
            cart->next->nextDirection = cart->direction;
        //cart->lastTile = currentTileAtDirection;
        //if (cart->next)
        //cart->next->nextDirection = cart->direction;
        cart->direction = cart->nextDirection;
    }

    return snapped;
}

void Drill::update(float dt, glm::vec2 direction, float speed, glm::vec2 pos) {

    glm::vec2 headTile = getCurrentTile(pos, direction);
    //accDt += dt;
    //head
    //drillNode->direction = direction;
    if (tailLength == 0) {
        return;
    }
//    if (tailLength > lastTailLength) {
//        append();
//        lastTailLength++;
//    }


    if (!createdFirstCart) {
        append();
        drillNode->position = (headTile - direction) * 16.0f;
        createdFirstCart = true;
        lastTailLength++;
        return;
    }

    drillNode->nextDirection = direction;
    Node *current = drillNode;
    //TODO: LAG really screws the carts up!
    while (current) {
        current->lastPosition = current->position;
        current->position += current->direction * speed;

        if (snapToGrid(current)) {

            if (tailLength > lastTailLength && current->lastTile != getCurrentTile(current->position, current->direction)) {
                append();
                lastTailLength++;
            }

            //bi::ioManager().renderer->drawTexture(current->position, {16, 16}, {1, 0, 1, 1}, cartTexId, 0);
            //bi::ioManager().shaperenderer->drawRect(current->position, {16, 16}, {0, 1, 0, 0.8f});
        }
        //        bi::ioManager().shaperenderer->drawRect(current->position, {16, 16}, {0, 1, 1, .4f});
        /*
        float angle = 0.0f;

        if (current->direction == down)
            angle = bi::math::degreesToRadians(90.0f);
        else if (current->direction == up) {
            angle = bi::math::degreesToRadians(-90.0f);
        } else if (current->direction == left) {
            angle = bi::math::degreesToRadians(180.0f);
        }
        bi::ioManager().renderer->drawTexture(current->position, {16, 16}, {1, 0, 1, 1}, cartTexId, angle);

         */
        current = current->next;
    }
}

void Drill::checkSkip(float speed, Node *current) {
    glm::vec currentTile = getCurrentTile(current->position, current->direction);
    if ((current->lastTile + current->direction) == currentTile) {

    } else if (current->lastTile == currentTile) {

    } else {
        bi::log("Skipped tiles!!!!!!!!!!!!!!!!!!!!!!!!!");
    }
}

void Drill::append() {

    if (appendPointer == nullptr) {

        Node *n = new Node();

        n->direction = glm::vec2{1, 0};
        n->nextDirection = glm::vec2{1, 0};
        appendPointer = n;
        n->number = 0;
        bi::log("First cart id :", this->appendPointer->number);
        drillNode = appendPointer;
        return;
    }
    Node *n = new Node();
    n->direction = this->appendPointer->direction;
    glm::vec2 negatedDir = (this->appendPointer->direction * -1.0f);
    n->position = this->appendPointer->lastTile * 16.0f;
    glm::vec2 currentTile = getCurrentTile(this->appendPointer->position, appendPointer->direction);
    n->nextDirection = appendPointer->direction;
    n->lastTile = this->appendPointer->lastTile + negatedDir;
    n->number = tailLength - 1;

    appendPointer->next = n;
    appendPointer = appendPointer->next;
    bi::log("new appended cartId:", this->appendPointer->number);
}


void Drill::appendNew() {

    if (appendPointer == nullptr) {

        Node *n = new Node();

        n->direction = glm::vec2{1, 0};
        n->nextDirection = glm::vec2{1, 0};
        appendPointer = n;
        n->number = 0;
        bi::log("First cart id :", this->appendPointer->number);
        drillNode = appendPointer;
        return;
    }

    Node *n = new Node();
    //glm::vec2 currentTile = getCurrentTile(appendPointer->position, appendPointer->direction);
    //glm::vec2 lastDirection =
    n->direction = this->appendPointer->direction;
    //glm::vec2 negatedDir = (lastDirection * -1.0f);
    n->position = this->appendPointer->lastTile * 16.0f;

    n->nextDirection = appendPointer->direction;
    //n->lastTile = this->appendPointer->lastTile + negatedDir;
    n->number = tailLength - 1;

    appendPointer->next = n;
    appendPointer = appendPointer->next;
    bi::log("new appended cartId:", this->appendPointer->number);
}

void Drill::prepend(glm::vec2 direction) {
    Node *node = new Node();
    node->direction = drillNode->direction;
    node->position = drillNode->position;
    drillNode->position = drillNode->lastTile * 16.0f;
    drillNode->nextDirection = node->direction;
    //node->position =
    node->next = drillNode;
    drillNode = node;
}

void Drill::init() {
    this->drillTexId = bi::ioManager().assetmanager->loadTexture(drillPath);
    this->cartTexId = bi::ioManager().assetmanager->loadTexture(cartPath);
    createAnimatedSprite();
    /*
    this->drillNode = new Node();
    this->drillNode->position = {16, 0};
    this->drillNode->direction = glm::vec2{1, 0};
    this->drillNode->nextDirection = glm::vec2{1, 0};
    this->drillNode->number = 0;
    //this->drillNode->parent = nullptr;
    Node *tail = this->drillNode;
     */

    /*
    for (int i = 17; i > 1; i--) {
        tail->next = new Node();
        tail->next->position = { i * 16, 2 * 16 };
        tail->next->direction = { 1, 0 };
        tail->next->nextDirection = { 1, 0 };
        tail->next->number = i;
        tail = tail->next;
    }
    */
    //this->appendPointer = tail;

    std::string str = "";

    bi::log("initializing drill");
}

void Drill::playAnimationRight(float dt, glm::vec2 position) {
    animatedSprite.play("right", dt, position);
}

void Drill::playAnimationLeft(float dt, glm::vec2 position) {
    animatedSprite.play("left", dt, position);
}

void Drill::playAnimationUp(float dt, glm::vec2 position) {
    animatedSprite.play("up", dt, position);
}

void Drill::playAnimationDown(float dt, glm::vec2 position) {
    animatedSprite.play("down", dt, position);
}

void Drill::playAnimation(float dt, std::string animationName, glm::vec2 position) {
    animatedSprite.play(animationName, dt, position);
}

void Drill::playAnimationByDirection(float dt, glm::vec2 direction, glm::vec2 position) {
    std::string animationName = "";
    if (direction == right) {
        animationName = "right";
    } else if (direction == left) {
        animationName = "left";
    } else if (direction == up) {
        animationName = "up";
    } else if (direction == down) {
        animationName = "down";
    } else {
        bi::ioManager().shaperenderer->drawRect(position, {16, 16}, {0, 0, 1, 1});
    }
    animatedSprite.play(animationName, dt, position);
}

void Drill::createAnimatedSprite() {

    std::vector<int> tileNumbers;

    tileNumbers.push_back(0);
    tileNumbers.push_back(1);
    tileNumbers.push_back(2);
    tileNumbers.push_back(3);

    animatedSprite.addAnimation("right", this->drillTexId, tileNumbers, {16.0f, 16.0f}, {1, 1, 1, 1}, 0.05f);

    tileNumbers.clear();

    tileNumbers.push_back(19);
    tileNumbers.push_back(20);
    tileNumbers.push_back(21);
    tileNumbers.push_back(22);

    animatedSprite.addAnimation("left", this->drillTexId, tileNumbers, {16.0f, 16.0f}, {1, 1, 1, 1}, 0.05f);

    tileNumbers.clear();

    tileNumbers.push_back(6);
    tileNumbers.push_back(7);
    tileNumbers.push_back(8);
    tileNumbers.push_back(9);

    animatedSprite.addAnimation("up", this->drillTexId, tileNumbers, {16.0f, 16.0f}, {1, 1, 1, 1}, 0.05f);

    tileNumbers.clear();

    tileNumbers.push_back(12);
    tileNumbers.push_back(13);
    tileNumbers.push_back(14);
    tileNumbers.push_back(15);

    animatedSprite.addAnimation("down", this->drillTexId, tileNumbers, {16.0f, 16.0f}, {1, 1, 1, 1}, 0.05f);
}

glm::vec2 Drill::getCurrentTile(glm::vec2 newPos, glm::vec2 dir) {
    glm::vec2 tileSize{16.0f, 16.0f};

    int currentX = static_cast<int>(newPos.x + (tileSize.x * .5f)) / tileSize.x;
    int currentY = static_cast<int>(newPos.y + (tileSize.y * .5f)) / tileSize.y;
    return {currentX, currentY};
}

glm::vec2 Drill::lastCurrentTile(glm::vec2 newPos, glm::vec2 dir) {
    glm::vec2 currentTile = {0, 0};
    glm::vec2 tileSize{16.0f, 16.0f};

    int currentx = 0;
    int currenty = 0;
    if (dir == up) {
        currentx = (int) (newPos.x) / tileSize.x;
        //currenty  = (int) (newPos.y + tileSize.y) / tileSize.y;
        currenty = (int) (newPos.y) / tileSize.y;
    }

    if (dir == down) {
        currentx = (int) (newPos.x) / tileSize.x;
        currenty = (int) (newPos.y + tileSize.y) / tileSize.y;
    }

    if (dir == left) {
        currentx = (int) (newPos.x) / tileSize.x;
        currenty = (int) (newPos.y) / tileSize.y;
    }

    if (dir == right) {
        currentx = (int) (newPos.x + tileSize.x) / tileSize.x;
        currenty = (int) (newPos.y) / tileSize.y;
    }

    currentTile = {currentx, currenty};
    //bi::log("currentTile" ,glm::to_string(currentTile));
    //currentTile = newPos) / tileSize * 16.0f;

    currentx = (int) (newPos.x + (tileSize.x / 2.0f)) / tileSize.x;
    currenty = (int) (newPos.y + (tileSize.y / 2.0f)) / tileSize.y;

    currentTile = {currentx, currenty};

    return currentTile;
}

void Drill::changeDirection(Node *cart) {
    cart->direction = cart->nextDirection;
}

void Drill::draw() {
    Node *current = drillNode;
    while (current) {
        float angle = 0.0f;

        if (current->direction == down)
            angle = bi::math::degreesToRadians(90.0f);
        else if (current->direction == up) {
            angle = bi::math::degreesToRadians(-90.0f);
        } else if (current->direction == left) {
            angle = bi::math::degreesToRadians(180.0f);
        }
        bi::ioManager().renderer->drawTexture(current->position, {16, 16}, {1, 0, 1, 1}, cartTexId, angle);

        current = current->next;
    }
}


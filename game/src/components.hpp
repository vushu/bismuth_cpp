#pragma once
#include <memory>
#include <bismuth/spriterenderer.hpp>
struct Movement {
    float x;
    float y;
};

struct Player {
    int batchId;
    int spriteId;
};

struct Block {
    int batchId;
    int spriteId;
};

struct Ball {
    float radius = 0.0f;
    int texId = 0;
    float posX, posY;
    float sizeX, sizeY;
    float angle;
};


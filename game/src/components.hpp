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


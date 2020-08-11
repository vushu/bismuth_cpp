#include <bismuth/spriterenderer.hpp>

#include <memory>
struct Movement {
    float x;
    float y;
};

struct Player {
    std::shared_ptr<bi::SpriteRenderer> sprite;
}


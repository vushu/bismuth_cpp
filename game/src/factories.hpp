#pragma once
#include <glm/glm.hpp>
#include <entt/entt.hpp>
namespace Factories {
    void createRect(entt::registry& registry ,glm::vec2 position, glm::vec2 size);
}

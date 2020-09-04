#include "components.hpp"
#include "factories.hpp"

void Factories::createRect(entt::registry& registry, glm::vec2 position, glm::vec2 size) {
    auto entity = registry.create();
    registry.emplace<Position>(entity, position.x, position.x);
    registry.emplace<Size>(entity, size.x, size.y);
}

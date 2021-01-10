#pragma once
#include <glm/glm.hpp>
namespace bi {
    namespace color {
        glm::vec4 toRGB(glm::vec4 color);
        glm::vec4 toRGB(float r, float g, float b, float a);
    }
}

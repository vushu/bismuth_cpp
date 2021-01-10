#include <bismuth/color.hpp>

using namespace bi;

glm::vec4 color::toRGB(glm::vec4 color) {
    if ((color.r > 1 && color.r <= 255) || (color.g > 1 && color.b <= 255) || (color.b > 1 && color.b <= 255)) {
        return {color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a};
    }
    return color;
}

glm::vec4 color::toRGB(float r, float g, float b, float a) {
    return toRGB(r,g,b,a);
}

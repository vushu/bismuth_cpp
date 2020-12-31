#include <bismuth/math.hpp>
#define M_PI 3.14159265358979323846
//
// Created by dhv on 12/31/20.
//

float bi::math::degreesToRadians(float degrees) {
    return (degrees * M_PI) / 180.0f;
}

float bi::math::radiansToDegrees(float radians) {
    return (radians * 180.0f) / M_PI;
}

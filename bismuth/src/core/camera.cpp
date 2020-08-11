#include "bismuth/logging.hpp"
#include <bismuth/camera.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>

using namespace bi;

Camera::Camera() {
    adjustProjection();
}

Camera::~Camera() {
    bi::log("Camera destroyed");
}

void Camera::adjustProjection() {

    projectionMatrix = glm::mat4(1.0);
    projectionMatrix = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    //projectionMatrix = glm::orthoRH(0.0f, 32.0f * 40.0f, 0.0f, 32.0f * 40.0f, 0.0f, 1.0f);
    //projectionMatrix = glm::orthoLH(0.0f, 225.0f * 40.0f, 0.0f, 225.0f * 21.0f, 0.0f, 100.0f);
}

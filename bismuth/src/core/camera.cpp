#include <bismuth/camera.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>

using namespace bi;

Camera::Camera() {
    adjustProjection();
}

Camera::~Camera() {}

void Camera::adjustProjection() {

    projectionMatrix = glm::orthoLH(0.0f, 32.0f * 40.0f, 0.0f, 32.0f * 21.0f, 0.0f, 100.0f);
}

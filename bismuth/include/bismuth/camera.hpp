#pragma once
#include "glm/fwd.hpp"
#include <glm/glm.hpp>
namespace bi {
    class Camera {
        public:
            // constructors, asssignment, destructor
            Camera(int w, int h) : width(w), height(h) {
                adjustProjection();
            }
            ~Camera ();

            void adjustProjection();
            glm::mat4 getViewMatrix();
            glm::mat4 projectionMatrix;
            glm::vec2 position{0,0};
            glm::mat4 viewMatrix = glm::mat4(1.0f);
            glm::mat4 inverseViewMatrix = glm::mat4(1.0f);
            glm::mat4 inverseProjectionMatrix = glm::mat4(1.0f);
            void setPosition(glm::vec2 pos);
            glm::mat4 getInversePV();
        private:
            float width, height;


    };

}

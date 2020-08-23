#pragma once
#include "glm/fwd.hpp"
#include <glm/glm.hpp>
namespace bi {
    class Camera {
        public:
            // constructors, asssignment, destructor
            Camera();
            ~Camera ();

            void adjustProjection();
            glm::mat4 getViewMatrix();
            glm::mat4 projectionMatrix;
            glm::vec2 position;
            glm::mat4 viewMatrix = glm::mat4(1.0f);
            void setPosition(glm::vec2 pos);
    };

}

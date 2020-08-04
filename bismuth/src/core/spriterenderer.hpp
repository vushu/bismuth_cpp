#pragma once
#include <glm/glm.hpp>
namespace bi  {
    class SpriteRenderer
    {
        public:
            SpriteRenderer ();
            ~SpriteRenderer();

            glm::vec4 color{1,1,1,1};
            bool isDirty;

        private:
    };
}

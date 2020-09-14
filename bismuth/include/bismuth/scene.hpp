#pragma once
#include <bismuth/renderer.hpp>
namespace bi {
    class Scene {
        public:
            Scene();

            ~Scene();
            virtual void update(float dt);
        protected:
            Renderer& getRenderer();
        private:

    };
}

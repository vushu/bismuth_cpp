#pragma once
#include <bismuth/scene.hpp>
namespace bi {
    class AssetEditor : public Scene {
        public:
            // constructors, asssignment, destructor
            AssetEditor();
            ~AssetEditor();
            void update(float dt);
            void init();
            void start();
            void close();

        private:

    };
}

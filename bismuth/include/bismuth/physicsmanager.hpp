#pragma once
namespace bi {
    class PhysicsManager{
        public:
            // constructors, asssignment, destructor
            PhysicsManager();
            ~PhysicsManager();
            void addPhysicObject();

        private:

    };

    const float M2P=32;
    const float P2M=1/M2P;
}

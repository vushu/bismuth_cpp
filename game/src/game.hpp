#pragma once
#include <bismuth/application.hpp>

class MyGame : public bi::Application {
    public:
        // constructors, asssignment, destructor
        MyGame() : bi::Application(800, 600, "MyGAME") {}
        ~MyGame();

    protected:
        void update(float dt) override;
        void init() override;

    private:

};

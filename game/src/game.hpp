#pragma once
#include <bismuth/bismuth.hpp>
class Game : public bi::Application{
    public:
        // constructors, asssignment, destructor
        Game() : bi::Application({480, 270}, {30,17,16,16}, "mygame", true) {}
        ~Game();
    private:

    protected:
        void update(float dt) override;
        void init() override;

};

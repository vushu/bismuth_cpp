#pragma once
#include <bismuth/bismuth.hpp>
class Game : public bi::Application{
    public:
        // constructors, asssignment, destructor
        Game() : bi::Application("bismuth") {}
        ~Game();
    private:

    protected:

        void init() override;
        void processInput(float dt) override;
        void update(float dt) override;
        void render(float dt) override;

};

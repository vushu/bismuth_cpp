# Bismuth Game lib  
A simple game library, with focus on simplicity.
## Installation  
```
sudo apt install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
```

## Creating a project  
The recommended way to create a project is to use bismuth-cli

```
mkdir ~/tools && cd ~/tools && git clone git@github.com:vushu/bismuth-cli.git
echo "PATH=$PATH:$HOME/tools/bismuth-cli/" >> ~/.bashrc
source ~/.bashrc

//For help
bismuth-cli -h

//For creating a blank project
bismuth-cli -n <projectname>
```

## Create a Scene  
inside you project run example:

```
bismuth -s MainMenuScene

```

## Building Game  

run the following command


```

//Do this command if it's first time
bismuth-cli -lubr

//pulls the latest bismuth_cpp from the github and saves it locally in ~/.bismuth
bismuth-cli -l

//updates your project with you current local version from ~/.bismuth
bismuth-cli -u

//builds
bismuth-cli -b

//run
bismuth-cli -r

//If you change code
bismuth-cli -br
```
## Quick Example 

```
bismuth-cli -n mygame
cd mygame
bismuth-cli -lu
bismuth-cli -s Scene1
bismuth-cli -s Scene2
```

game.cpp

``` 
#include "game.hpp"
#include "bismuth/color.hpp"
#include "bismuth/keylistener.hpp"
#include "scenes/scene1.hpp"
#include "scenes/scene2.hpp"
#include <memory>

Game::~Game() {}

void Game::init() {
    getSceneManager().addScene("scene1", std::make_unique<Scene1>());
    getSceneManager().addScene("scene2", std::make_unique<Scene2>());
}
void Game::processInput(float dt) { }
void Game::update(float dt) { }
void Game::render(float dt) { }
```
scene1.cpp

```
#include "scene1.hpp"
#include "bismuth/color.hpp"
#include "bismuth/keylistener.hpp"

Scene1::Scene1() {}

Scene1::~Scene1() {}

void Scene1::init() {
}

void Scene1::start() {}

void Scene1::processInput(float dt) {

    if (bi::keyInput().isKeyPressed(GLFW_KEY_F)) {
        getWindow().fullscreen();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_ESCAPE)) {
        this->getWindow().close();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_LEFT)) {
        this->nextScene = "scene2";
        bi::log("nextscene 2");
    }
}

void Scene1::update(float dt) {}

void Scene1::render(float dt) {
    getRenderer().clear();
    getRenderer().drawText("Hello this is Scene1", {100,200}, getAssetManager().getDefaultFont(), bi::color::SOFT_RED, 0.5);

    getShapeRenderer().drawLine({100,0}, {100,100}, bi::color::SOFT_YELLOW);
    getShapeRenderer().endFlushBegin();
    getRenderer().endFlushBegin();
}

void Scene1::close() {}
```

scene2.hpp
```
#pragma once
#include "bismuth/scene.hpp"
class Scene2 : public bi::Scene {
    public:
        Scene2();
        ~Scene2();

        void init() override;
        void start() override;
        void processInput(float dt) override;
        void update(float dt) override;
        void render(float dt) override;
        void close() override;
    private:
        glm::vec2 circlePosition {100, 100};
        glm::vec2 circleDirection {300, 300};
        bool isFullScreen = false;
        int maxHeight;
        int maxWidth;
};

```
scene2.cpp
```
#include "scene2.hpp"
#include "bismuth/color.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"

Scene2::Scene2() {}

Scene2::~Scene2() {}

void Scene2::init() {
    maxHeight = getWindow().height;
    maxWidth = getWindow().width;

}

void Scene2::start() {}

void Scene2::processInput(float dt) {

    if (bi::keyInput().isKeyPressed(GLFW_KEY_F)) {
        getWindow().fullscreen();
        isFullScreen = true;
    }
    if (bi::keyInput().isKeyPressed(GLFW_KEY_ESCAPE)) {
        this->getWindow().close();
    }

    if (bi::keyInput().isKeyPressed(GLFW_KEY_RIGHT)) {
        this->nextScene = "scene1";
        bi::log("nextscene 1");
    }
}

void Scene2::update(float dt) {

    circlePosition += dt * circleDirection;

    if (circlePosition.y + 10  > maxHeight) {
        circleDirection *= glm::vec2{1,-1};
    }

    if (circlePosition.y - 10 < 0) {
        circleDirection *= glm::vec2{1,-1};
    }

    if (circlePosition.x + 10 > maxWidth) {
        circleDirection *= glm::vec2{-1,1};
    }

    if (circlePosition.x - 10 < 0) {
        circleDirection *= glm::vec2{-1,1};
    }

}

void Scene2::render(float dt) {
    getRenderer().clear();
    getRenderer().drawText("Hello this is Scene2 ", {100, 200}, getAssetManager().getDefaultFont(), bi::color::SOFT_MAGENTA, 0.5);
    getShapeRenderer().drawPolygon(circlePosition, 20, 12, bi::color::SOFT_ORANGE, 0);
    getShapeRenderer().fill();
    getShapeRenderer().endFlushBegin();
    getRenderer().endFlushBegin();
}

void Scene2::close() {}
```
inside mygame folder, build and run using
```
bismuth-cli -br
```

## Some words
This is still a work in progress and a learning progress for me creating this library :)

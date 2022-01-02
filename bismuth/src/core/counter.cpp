#include <bismuth/utils/counter.hpp>
using namespace bi::utils;

bool Counter::countDown(float dt) {
    return counting(dt, false);
}

bool Counter::countUp(float dt) {
    return counting(dt, true);
}

bool Counter::counting(float dt, bool increment) {
    accumulatedTime += dt;
    if (accumulatedTime > interval){
        accumulatedTime = 0;
        counter += (increment ? 1 : -1);
        return true;
    }
    return false;
}

int Counter::getCount() {
    return counter;
}

void Counter::setCount(int count) {
    counter = count;
}

void Counter::resetCount() {
    counter = initialCount;
}

#include <bismuth/utils/counter.hpp>
using namespace bi::utils;

void Counter::updateDecrement(float dt) {
    counting(dt, false);
}

void Counter::updateIncrement(float dt) {
    counting(dt, true);
}

void Counter::start() {
    startCount = true;
}

void Counter::stop() {
    startCount = false;
}

void Counter::counting(float dt, bool increment) {
    if (!startCount) {
        return;
    }
    accumulatedTime += dt;
    if (accumulatedTime > interval){
        accumulatedTime = 0;
        counter += (increment ? 1 : -1);
        countdownCallback(counter);
    }
}

void Counter::onCount(CountdownCallback callback) {
    this->countdownCallback = callback;
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

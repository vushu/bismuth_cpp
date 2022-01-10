#pragma once
#include <functional>
namespace bi {
    namespace utils {
        class Counter{
            public:
                typedef std::function<void(int)> CountdownCallback;
                Counter(int initialCount, float interval) : initialCount(initialCount), interval(interval), counter(initialCount) {};
                ~Counter() {};
                void updateIncrement(float dt);
                void updateDecrement(float dt);
                int getCount();
                void setCount(int count);
                void resetCount();
                void onCount(CountdownCallback callback);
                void start();
                void stop();


            private:
                bool startCount = false;
                void counting(float dt, bool increment);
                int initialCount;
                float accumulatedTime = 0, interval;
                int counter;
                CountdownCallback countdownCallback;


        };
    }
}

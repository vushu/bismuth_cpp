#pragma once
namespace bi {
    namespace utils {
        class Counter{
            public:
                // constructors, assignment, destructor
                Counter(int initialCount, float interval) : initialCount(initialCount), interval(interval), counter(initialCount) {};
                ~Counter() {};
                bool countDown(float dt);
                bool countUp(float dt);
                int getCount();
                void setCount(int count);
                void resetCount();


            private:
                bool counting(float dt, bool increment);
                int initialCount;
                float accumulatedTime = 0, interval;
                int counter;


        };
    }
}

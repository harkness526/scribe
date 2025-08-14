#include <clock/adding_clock/AddingClock.h>

#include <chrono>
#include <functional>
#include <iostream>
#include <utility>

using namespace std::chrono;

nanoseconds bench(std::function<void()> f)
{
    auto start = steady_clock::now();
    f();
    auto elapsed = duration_cast<nanoseconds>(steady_clock::now() - start);

    return elapsed;
}

int bench(int argc, char* argv[])
{
    AddingClock loggerClock;
    constexpr const long long ITERATIONS = 100000000;

    auto resSys = bench([]() {
        for (int i = 0; i < ITERATIONS; ++i) {
            volatile auto now = system_clock::now();
        }
    });
    std::cout << "Sys Clock Time: " << resSys / 1ms << std::endl;

    auto resClock = bench([&loggerClock]() {
        for (int i = 0; i < ITERATIONS; ++i) {
            volatile auto now = steady_clock::now();
            // volatile auto now = loggerClock.getTime();
        }
    });
    std::cout << "Log Clock Time: " << resClock / 1ms << std::endl;

    return 0;
}

#pragma once
#include <chrono>

class LoggerClock {
public:
    virtual ~LoggerClock() = default;
    virtual std::chrono::time_point<std::chrono::system_clock> getTime() = 0;
};

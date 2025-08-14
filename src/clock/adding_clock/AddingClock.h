#pragma once
#include <clock/LoggerClock.h>

#include <chrono>

class AddingClock : public LoggerClock
{
private:
    std::chrono::time_point<std::chrono::system_clock> localSystemEpoch_;
    std::chrono::time_point<std::chrono::steady_clock> localSteadyEpoch_;

public:
    AddingClock();
    ~AddingClock() override = default;

    std::chrono::time_point<std::chrono::system_clock> getTime() override;
};

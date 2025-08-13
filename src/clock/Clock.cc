#include <Clock.h>

LoggerClock::LoggerClock()
    : localSystemEpoch_(std::chrono::system_clock::now()),
      localSteadyEpoch_(std::chrono::steady_clock::now())
{}

std::chrono::time_point<std::chrono::system_clock> LoggerClock::getTime()
{
    auto elapsed = std::chrono::steady_clock::now() - localSteadyEpoch_;
    auto secondsFromClockStart =
        std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed);

    return localSystemEpoch_ + secondsFromClockStart;
}

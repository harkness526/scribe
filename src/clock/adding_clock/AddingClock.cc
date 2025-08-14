#include <clock/adding_clock/AddingClock.h>

AddingClock::AddingClock()
    : localSystemEpoch_(std::chrono::system_clock::now()),
      localSteadyEpoch_(std::chrono::steady_clock::now())
{}

std::chrono::time_point<std::chrono::system_clock> AddingClock::getTime()
{
    using namespace std::chrono;
    auto elapsed = steady_clock::now() - localSteadyEpoch_;
    auto secondsFromClockStart = duration_cast<nanoseconds>(elapsed);

    return localSystemEpoch_ + secondsFromClockStart;
}

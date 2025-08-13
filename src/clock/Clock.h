#include <chrono>

class LoggerClock {
private:
    std::chrono::time_point<std::chrono::system_clock> localSystemEpoch_;
    std::chrono::time_point<std::chrono::steady_clock> localSteadyEpoch_;

public:
    LoggerClock();
    ~LoggerClock() = default;
    
    std::chrono::time_point<std::chrono::system_clock> getTime();
};

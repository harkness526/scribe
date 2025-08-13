#include <clock/Clock.h>

#include <cassert>
#include <iostream>
#include <thread>

using namespace std::chrono;

#define EXPECT_EQ(left, right)                                                \
    if (left == right) {                                                      \
    } else {                                                                  \
        std::cout << "EXPECT_EQ FAILED AT " << __FILE__ << ", line "          \
                  << __LINE__ << std::endl;                                   \
        std::cout << "left = " << left << ", right = " << right << std::endl; \
        return -1;                                                            \
    }

int create(int argc, char* argv[])
{
    LoggerClock loggerClock;
    for (int i = 0; i < 100; ++i) {
        auto now = system_clock::now();
        auto clockTime = loggerClock.getTime();

        auto sys_sec =
            duration_cast<milliseconds>(now.time_since_epoch()).count();
        
        auto clock_sec =
            duration_cast<milliseconds>(clockTime.time_since_epoch()).count();

        EXPECT_EQ(sys_sec, clock_sec);
        std::this_thread::sleep_for(milliseconds(std::rand() % 20));
    }

    return 0;
}

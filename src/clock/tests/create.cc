#include <clock/adding_clock/AddingClock.h>
#include <gtest/gtest.h>

#include <cassert>
#include <iostream>
#include <thread>

using namespace std::chrono;

TEST(Clock, Create)
{
    AddingClock loggerClock;
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
}

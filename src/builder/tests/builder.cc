#include <builder/plane/PlaneBuilder.h>
#include <gtest/gtest.h>

#include <chrono>
#include <iostream>

TEST(Builder, SimpleEntry)
{
    PlaneBuilder builder;
    std::string logEntry = builder.build(__FILE__,
                                         __LINE__,
                                         std::chrono::system_clock::now(),
                                         "I am a Log Entry");

    std::cout << logEntry << std::endl;
}

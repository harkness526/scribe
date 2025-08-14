#include <builder/plane/PlaneBuilder.h>

#include <chrono>
#include <iostream>

int builder(int argc, char* argv[])
{
    PlaneBuilder builder;
    std::string logEntry = builder.build(__FILE__,
                                         __LINE__,
                                         std::chrono::system_clock::now(),
                                         "I am a Log Entry");

    std::cout << logEntry << std::endl;
    return 0;
}

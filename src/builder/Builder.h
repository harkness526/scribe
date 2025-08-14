#pragma once
#include <chrono>
#include <string>

class Builder
{
public:
    virtual ~Builder() = default;
    virtual std::string build(
        const char* file,
        int line,
        std::chrono::time_point<std::chrono::system_clock> time,
        std::string&& msg) = 0;
};

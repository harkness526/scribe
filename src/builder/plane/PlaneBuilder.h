#pragma once
#include <builder/Builder.h>


class PlaneBuilder : public Builder
{
public:
    PlaneBuilder() = default;
    
    ~PlaneBuilder() override = default;
    
    std::string build(const char* file,
                      int line,
                      std::chrono::time_point<std::chrono::system_clock> time,
                      std::string&& msg) override;
};

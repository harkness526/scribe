#pragma once
#include <builder/Builder.h>


class FormattedBulder : public Builder
{
public:
    FormattedBulder();
    ~FormattedBulder() override = default;
    std::string build(const char* file,
                      int line,
                      std::chrono::time_point<std::chrono::system_clock> time,
                      std::string&& msg) override;
};

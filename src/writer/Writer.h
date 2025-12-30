#pragma once
#include <string>

class Writer
{
public:
    virtual ~Writer() = default;

    virtual void write(std::string&& entry) = 0;
    virtual void write(const std::string& entry) = 0;
};

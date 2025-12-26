#pragma once

#include <Writer.h>

class SyncWriter : public Writer
{
public:
    SyncWriter(std::string filename);
    ~SyncWriter() = default;

    virtual void write(std::string&& entry) override;
private:
    std::string fileName_;
};

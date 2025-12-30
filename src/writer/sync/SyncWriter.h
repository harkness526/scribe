#pragma once
#include <Writer.h>

#include <filesystem>
#include <fstream>

class SyncWriter : public Writer
{
public:
    SyncWriter(std::filesystem::path folder, std::string base, size_t maxSize, size_t maxFiles);
    ~SyncWriter() = default;

    virtual void write(std::string&& entry) override;
    virtual void write(const std::string& entry) override;

protected:
    std::filesystem::path createLogFilename(size_t fileIdx);
    size_t parseLogFilename(std::string logFilename);
    size_t findOldestLogIdx();

    void roll();
    void preLaunchCleanup();
private:
    std::filesystem::path folder_;
    std::string baseFileName_;
    size_t currentSize_{0};
    size_t maxFiles_{1};
    size_t maxSize_{1024};

    std::ofstream log_;
};

#include "SyncWriter.h"
#include <fstream>

namespace fs = std::filesystem;

SyncWriter::SyncWriter(std::filesystem::path folder,
                       std::string base,
                       size_t maxSize,
                       size_t maxFiles)
    : folder_(std::move(folder)),
      baseFileName_(std::move(base)),
      maxSize_(maxSize),
      maxFiles_(maxFiles)
      
{
    preLaunchCleanup();
    
    log_ = std::ofstream(createLogFilename(0), std::ios_base::app);
    if (!log_) {
        throw "Cant Open log file";
    }    
};

void SyncWriter::write(std::string&& entry)
{
    if (currentSize_ + entry.size() > maxSize_) {
        roll();

    }
    
    log_ << entry << std::endl;

    currentSize_ += entry.size() + 1;
}

void SyncWriter::roll()
{
    log_.flush();
    int maxLogIdx = maxFiles_ - 1;
    
    for (int i = maxLogIdx; i >= 0; --i) {
        fs::path log = createLogFilename(i);
        if (!fs::exists(log)) {
            continue;
        }

        if (i == maxLogIdx) {
            fs::remove(log);
            continue;
        }

        fs::rename(log, createLogFilename(i + 1));
    }
    
    log_ = std::ofstream(createLogFilename(0), std::ios_base::app);
    currentSize_ = 0;
}

fs::path SyncWriter::createLogFilename(size_t fileIdx)
{
    std::string logFilename = fileIdx > 0 ? baseFileName_ + "." + std::to_string(fileIdx) : baseFileName_;
    return folder_ / logFilename;
}

size_t SyncWriter::parseLogFilename(std::string logFilename)
{
    if (logFilename == baseFileName_) {
        return 0;
    }
    
    auto number = logFilename.substr(baseFileName_.size());
    return std::stoi(number);
}

size_t SyncWriter::findOldestLogIdx()
{
    size_t maxLogIdx = 0;
    for (const auto& dir_entry : fs::directory_iterator(folder_)) {
        std::string filename = dir_entry.path().filename().string();
        if (filename.starts_with(baseFileName_)) {
            maxLogIdx = std::max(maxLogIdx, parseLogFilename(filename));
        }
    }

    return maxLogIdx;
}

void SyncWriter::preLaunchCleanup()
{
    size_t oldestLogIdx = findOldestLogIdx();
    if (oldestLogIdx <= maxFiles_) {
        return;
    }

    for (size_t i = maxFiles_; i < oldestLogIdx; ++i) {
        fs::remove(createLogFilename(i));
    }
}

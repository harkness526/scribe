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
    size_t oldestLogIdx = findOldestLogIdx();
    
    log_ = std::ofstream(createLogFilename(0), std::ios_base::app);
    if (!log_) {
        throw "Cant Open log file";
    }    
};

void SyncWriter::write(std::string&& entry)
{
    if (currentSize_ + entry.size() > maxSize_) {
        roll();
        log_ = std::ofstream(createLogFilename(0), std::ios_base::app);
    }
    
    log_ << entry << std::endl;

    currentSize_ += entry.size() + 1;
}

void SyncWriter::roll()
{
    log_.flush();
    for (int i = maxFiles_; i >= 0; --i) {
        fs::path log = createLogFilename(i);
        if (!fs::exists(log)) {
            continue;
        }

        if (i == maxFiles_) {
            fs::remove(log);
            continue;
        }

        fs::rename(log, createLogFilename(i + 1));
    }
}

fs::path SyncWriter::createLogFilename(size_t fileIdx)
{
    std::string logFilename = fileIdx > 0 ? baseFileName_ + "." + std::to_string(fileIdx) : baseFileName_;
    return folder_ / logFilename;
}

size_t SyncWriter::parseLogFilename(std::string logFilename)
{
    return std::stoi(logFilename.substr(baseFileName_.size()));
}

size_t SyncWriter::findOldestLogIdx()
{
    size_t amount = 0;
    for (const auto& dir_entry : fs::directory_iterator(folder_)) {
        if (dir_entry.path().filename().string().starts_with(baseFileName_)) {
            ++amount;
        }
    }

    return amount;
}

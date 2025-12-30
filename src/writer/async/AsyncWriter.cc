#include "AsyncWriter.h"
#include <iostream>

namespace fs = std::filesystem;

AsyncWriter::AsyncWriter(std::filesystem::path folder, std::string base, size_t maxSize, size_t maxFiles)
    : SyncWriter::SyncWriter(std::move(folder), std::move(base), maxSize, maxFiles)
{
    worker_ = std::thread(&AsyncWriter::worker, this);
}

AsyncWriter::~AsyncWriter()
{
    {
        std::unique_lock lock(m_);
        shouldStop_ = true;
    }

    cv_.notify_one();

    if (worker_.joinable()) {
        worker_.join();
    }
}

void AsyncWriter::write(std::string&& entry)
{
    {
        std::unique_lock lock(m_);
        queue_.push(std::move(entry));
    }

    cv_.notify_one();
}

void AsyncWriter::write(const std::string& entry)
{
    {
        std::unique_lock lock(m_);
        queue_.push(entry);
    }

    cv_.notify_one();
}

void AsyncWriter::worker()
{
    std::unique_lock lock(m_);
    while(!shouldStop_) {
        cv_.wait(lock, [this] () {
            return shouldStop_ || !queue_.empty();
        });

        while (!queue_.empty()) {
            SyncWriter::write(queue_.front());
            queue_.pop();
        }
    }
}

#pragma once
#include <sync/SyncWriter.h>

#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>

class AsyncWriter : public SyncWriter
{
public:
    AsyncWriter(std::filesystem::path folder, std::string base, size_t maxSize, size_t maxFiles);
    ~AsyncWriter() override;
    
    virtual void write(std::string&& entry) override;
    virtual void write(const std::string& entry) override;

private:
    void worker();

    std::queue<std::string> queue_;
    
    bool shouldStop_{false};
    
    std::condition_variable cv_;
    std::thread worker_;
    std::mutex m_;    
};

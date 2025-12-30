#include <writer/sync/SyncWriter.h>

#include <gtest/gtest.h>

#include <filesystem>
#include <vector>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

std::string genRandomString(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

std::string readFileContent(fs::path file)
{
    std::ifstream written(file);
    std::stringstream fileContent;
    fileContent << written.rdbuf();

    return fileContent.str();
}

TEST(SyncWriter, WriteFixed)
{
    std::string log = "sync_writer.log";
    std::filesystem::path path = std::filesystem::current_path();
    
    std::string msg1 = "I am a first entry";
    std::string msg2 = "I am a second entry";
    std::string msg3 = "I am a third entry";
    
    std::string fullLog = msg1 + "\n" + msg2 + "\n" + msg3 + "\n";

    SyncWriter writer(path, log, 100, 1);

    writer.write(std::move(msg1));
    writer.write(std::move(msg2));
    writer.write(std::move(msg3));

    std::ifstream written(log);
    ASSERT_TRUE(written);
    std::stringstream fileContent;
    
    fileContent << written.rdbuf();
                   
    EXPECT_EQ(fullLog, fileContent.str());

    std::filesystem::remove(log);
}

TEST(SyncWriter, WriteRandomString)
{
    std::srand((unsigned)time(NULL) * getpid());
    
    std::string log = "sync_writer_" + genRandomString(10);
    std::filesystem::path path = std::filesystem::current_path();
    
    std::string fullLog;
    SyncWriter writer(path, log, 1000000, 1);

    for (int i = 0; i < 1000; ++i) {
        int len = 100 + std::rand() % 50;
        std::string entry = genRandomString(len);
        fullLog.append(entry + "\n");
        
        writer.write(std::move(entry));
    }

    std::ifstream written(log);
    ASSERT_TRUE(written);
    std::stringstream fileContent;
    fileContent << written.rdbuf();

    EXPECT_EQ(fullLog, fileContent.str());

    std::filesystem::remove(log);
}

TEST(SyncWriter, RollWithOneWrite)
{
    constexpr const int LOG_COUNT = 10;
    std::srand((unsigned)time(NULL) * getpid());

    std::string logBaseName  = "sync_writer.log";
    std::vector<fs::path> logs;
    for (int i = 0; i < LOG_COUNT; ++i) {
        std::string logName = i == 0 ? logBaseName : logBaseName + "." + std::to_string(i);
        fs::path log = fs::current_path()/logName;
        logs.push_back(log);
    }

    for(const auto& log: logs) {
        EXPECT_FALSE(fs::exists(log));
    }

    std::vector<std::string> entries;
    for (int i = 0; i < 100; ++i) {
        int len = 100 + std::rand() % 50;
        std::string entry = genRandomString(len);
        
        entries.push_back(entry);
    }
    
    SyncWriter writer(fs::current_path(), logBaseName, 150, LOG_COUNT);
    for (auto entry: entries) {
        writer.write(std::move(entry));
    }

    auto it = entries.rbegin();
    for (const auto& log: logs) {
        ASSERT_TRUE(fs::exists(log));
        std::string content = readFileContent(log);
        EXPECT_EQ(content, *it + "\n");
        it++;
    }
    
    for (const auto& log: logs) {
        std::filesystem::remove(log);
    }
}

TEST(SyncWriter, checkLogsOnConstruction)
{
    constexpr const int LOG_COUNT = 10;
    constexpr const int NEEDED_LOG_COUNT = 1;
    std::srand((unsigned)time(NULL) * getpid());

    auto testForNeeded = [](int logCount, int neddedLogCount) {
        std::string logBaseName  = "sync_writer.log";
        std::vector<fs::path> logs;
        for (int i = 0; i < logCount; ++i) {
            std::string logName = i == 0 ? logBaseName : logBaseName + "." + std::to_string(i);
            fs::path log = fs::current_path()/logName;
            std::ofstream f(log);

            logs.push_back(log);
        }

        for(const auto& log: logs) {
            EXPECT_TRUE(fs::exists(log));
        }
    
        SyncWriter writer(fs::current_path(), logBaseName, 100, neddedLogCount);

        for(int i = 0; i < logCount; ++i) {
            if (i < neddedLogCount) {
                EXPECT_TRUE(fs::exists(logs[i]));
            } else {
                EXPECT_FALSE(fs::exists(logs[i]));
            }
        }

        for (const auto& log: logs) {
            std::filesystem::remove(log);
        }
    };

    for (int logCount = 10; logCount > 0; --logCount) {
        for (int neddedLogCount = 1; neddedLogCount < 10; ++neddedLogCount) {
            testForNeeded(logCount, neddedLogCount);
        }
    }
}

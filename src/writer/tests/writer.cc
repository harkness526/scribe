#include <writer/sync/SyncWriter.h>

#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <filesystem>

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

TEST(SyncWriter, WriteFixed)
{
    std::string log = "./sync_writer.log";

    std::string msg1 = "I am a first entry";
    std::string msg2 = "I am a second entry";
    std::string msg3 = "I am a third entry";
    
    std::string fullLog = msg1 + "\n" + msg2 + "\n" + msg3 + "\n";

    SyncWriter writer(log);

    writer.write(std::move(msg1));
    writer.write(std::move(msg2));
    writer.write(std::move(msg3));

    std::ifstream written(log);
    std::stringstream fileContent;
    
    fileContent << written.rdbuf();
                   
    EXPECT_EQ(fullLog, fileContent.str());

    std::filesystem::remove(log);
}

TEST(SyncWriter, WriteRandomString)
{
    std::srand((unsigned)time(NULL) * getpid());
    
    std::string log = "./sync_writer_" + genRandomString(10) + ".log";
    
    std::string fullLog;
    SyncWriter writer(log);

    for (int i = 0; i < 1000; ++i) {
        int len = 100 + std::rand() % 50;
        std::string entry = genRandomString(len);
        fullLog.append(entry + "\n");
        
        writer.write(std::move(entry));
    }

    std::ifstream written(log);
    std::stringstream fileContent;
    fileContent << written.rdbuf();

    EXPECT_EQ(fullLog, fileContent.str());

    std::filesystem::remove(log);
}

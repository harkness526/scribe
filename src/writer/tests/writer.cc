#include <writer/sync/SyncWriter.h>

#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <filesystem>

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

#include <writer/sync/SyncWriter.h>
#include <writer/async/AsyncWriter.h>

#include <gtest/gtest.h>

#include <filesystem>
#include <vector>
#include <chrono>

namespace fs = std::filesystem;
namespace ch = std::chrono;

static std::string genRandomString(const int len) {
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

TEST(WriterBenchmark, SyncVsAsync)
{
    constexpr const int LOOPS = 100000;
    fs::path tmpLogDir = fs::current_path() / "writer_bm";
    fs::create_directory(tmpLogDir);
    
    AsyncWriter aWriter(tmpLogDir, "async.log", 4096, 5);
    SyncWriter sWriter(tmpLogDir, "sync.log", 4096, 5);

    std::vector<std::string> entries;
    for (int i = 0; i < LOOPS; ++i) {
        int len = 100 + std::rand() % 50;
        entries.push_back(genRandomString(len));
    }

    {
        auto before = ch::steady_clock::now();
        for (const auto& entry: entries) {
            sWriter.write(entry);
        }
        auto result = ch::duration_cast<ch::microseconds>(ch::steady_clock::now() - before).count();
        std::cout << "SyncWriter took: " << result << " us,"
                  << " on average: " << result/LOOPS << std::endl;
    }

  
    {
        auto before = ch::steady_clock::now();
        for (const auto& entry: entries) {
            aWriter.write(entry);
        }
        auto result = ch::duration_cast<ch::microseconds>(ch::steady_clock::now() - before).count();
        std::cout << "AsyncWriter took: " << result << " us,"
                  << " on average: " << result/LOOPS << std::endl;
    }

    std::filesystem::remove_all(tmpLogDir);
}

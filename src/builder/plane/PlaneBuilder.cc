#include <builder/plane/PlaneBuilder.h>

#include <array>
#include <cstring>
#include <sstream>

std::string PlaneBuilder::build(
    const char* file,
    int line,
    std::chrono::time_point<std::chrono::system_clock> time,
    std::string&& msg)
{
    file = strrchr(file, '/') + 1;

    std::time_t tt = std::chrono::system_clock::to_time_t(time);

    std::array<char, 32> timeBuf;
    timeBuf.fill(0);

    std::strftime(timeBuf.data(), timeBuf.size(), "%c", std::gmtime(&tt));

    std::stringstream ss;
    ss << timeBuf.data() << " " << msg << " [" << file << ":" << line << "]\n";

    return ss.str();
}

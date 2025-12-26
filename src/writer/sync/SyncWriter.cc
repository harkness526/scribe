#include "SyncWriter.h"
#include <fstream>

SyncWriter::SyncWriter(std::string filename) : fileName_(std::move(filename)){};

void SyncWriter::write(std::string&& entry)
{
    std::ofstream log(fileName_, std::ios_base::app);
    if (!log) {
        throw "Cant Open log file";
    }

    log << entry << std::endl;
}

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "du_modern.hpp"

std::string humanReadableSize(int bytes)
{
    int totalUnits = 5;
    std::vector<std::string> units = {"B", "K", "M", "G", "T"};
    int i = 0;

    while (bytes >= 1024 && i < totalUnits - 1)
    {
        bytes /= 1024;
        i++;
    }

    return std::to_string(bytes) + units[i];
};

void log_entity_data(const fs::path& displayPath, int entitySize, bool humanReadable)
{
    std::string adaptedEntitySize =
        std::move(humanReadable ? humanReadableSize(entitySize) : std::to_string(entitySize));

    std::cout << adaptedEntitySize << "\t" << displayPath.string() << "\n";
}

uint32_t du_modern(const fs::path& entityPath, const DuFlags& options)
{
    int totalSize = 0;

    for (const auto& entry : fs::directory_iterator(entityPath))
    {
        if (entry.is_directory())
        {
            totalSize += du_modern(entry.path(), options);
        }
        else
        {
            totalSize += entry.file_size();

            if (options.showFiles)
            {
                log_entity_data(entry.path(), entry.file_size(), options.humanReadable);
            }
        }
    }

    log_entity_data(entityPath, totalSize, options.humanReadable);
    return totalSize;
}

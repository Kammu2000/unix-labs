#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

struct GrepOptions
{
    bool shouldRecurse;
    std::string pattern;
    std::vector<fs::path> paths;
};

GrepOptions parse(int argc, char* argv[]);

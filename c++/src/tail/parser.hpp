#pragma once

#include <string>
#include <vector>

struct TailOptions
{
    std::vector<std::string> fileNames;
    int count;
};

TailOptions parse(int argc, char* argv[]);

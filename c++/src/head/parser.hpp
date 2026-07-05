#pragma once

#include <string>
#include <vector>

struct HeadOptions
{
    std::vector<std::string> fileNames;
    int count;
};

HeadOptions parse(int argc, char* argv[]);

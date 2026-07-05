#pragma once

#include <string>
#include <vector>

struct XargsOption
{
    std::vector<std::string> command;
};

XargsOption parse(int argc, char* argv[]);

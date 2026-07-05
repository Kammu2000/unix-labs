#include <cstddef>
#include <string>
#include <vector>

#include "parser.hpp"

XargsOption parse(int argc, char* argv[])
{
    std::vector<std::string> command;

    for (size_t i = 1; i < argc; i++)
    {
        command.push_back(argv[i]);
    }

    return {command};
}

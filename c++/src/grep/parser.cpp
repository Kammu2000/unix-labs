#include <string>
#include <unistd.h>

#include "parser.hpp"

GrepOptions parse(int argc, char* argv[])
{
    bool shouldRecurse{false};
    std::string pattern;
    std::vector<fs::path> paths;

    int opt;
    // set opterr to 0 to avoid silent error messages from getopt
    opterr = 0;

    while ((opt = getopt(argc, argv, "r")) != -1)
    {
        switch (opt)
        {
            case 'r': {
                shouldRecurse = true;
                break;
            }

            case '?': {
                throw std::runtime_error("Unknown flag: " +
                                         std::string(1, static_cast<char>(optopt)));
                break;
            }
        }
    }

    for (size_t i = optind; i < argc; i++)
    {
        if (i == optind)
        {
            pattern = argv[i];
            continue;
        }

        paths.push_back(argv[i]);
    }

    return {shouldRecurse, pattern, paths};
}

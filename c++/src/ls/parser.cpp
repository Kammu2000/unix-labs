#include <stdexcept>
#include <unistd.h>
#include <vector>

#include "parser.hpp"

LsOptions parse(int argc, char* argv[])
{
    std::vector<fs::path> dir_paths;
    LsFlags flags{.showHiddenFiles = false, .isLongListFormat = false};
    int opt;
    // set opterr to 0 to avoid silent error messages from getopt
    opterr = 0;

    while ((opt = getopt(argc, argv, "al")) != -1)
    {
        switch (opt)
        {
            case 'a': {
                flags.showHiddenFiles = true;
                break;
            }

            case 'l': {
                flags.isLongListFormat = true;
                break;
            }

            case '?': {
                throw std::runtime_error("Unknown flag: " +
                                         std::string(1, static_cast<char>(optopt)));
            }
        }
    }

    for (int i = optind; i < argc; i++)
    {
        dir_paths.push_back(argv[i]);
    }

    if (dir_paths.size() == 0)
    {
        dir_paths.push_back(".");
    }

    return {flags, dir_paths};
}

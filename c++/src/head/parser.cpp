#include <cstdlib>
#include <unistd.h>

#include "parser.hpp"
#include "utils.hpp"

HeadOptions parse(int argc, char* argv[])
{
    std::vector<std::string> fileNames;
    int count = 0;
    int opt;
    // set opterr to 0 to avoid silent error messages from getopt
    opterr = 0;

    while ((opt = getopt(argc, argv, "n:")) != -1)
    {
        switch (opt)
        {
            case 'n': {
                count = parseInt(optarg);
                break;
            }

            case '?': {
                if (optopt == 'n')
                {
                    throw std::runtime_error("Missing value for -n");
                }

                throw std::runtime_error("Unknown flag: " +
                                         std::string(1, static_cast<char>(optopt)));
            }
        }
    }

    for (int i = optind; i < argc; i++)
    {
        fileNames.push_back(argv[i]);
    }

    return {fileNames, count};
}

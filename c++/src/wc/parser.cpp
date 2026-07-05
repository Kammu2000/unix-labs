#include <string>
#include <unistd.h>
#include <vector>

#include "parser.hpp"

WcOptions parse(int argc, char* argv[])
{
    bool lines = false, words = false, bytes = false, characters = false;
    std::vector<std::string> fileNames;

    int opt;
    // set opterr to 0 to avoid silent error messages from getopt
    opterr = 0;

    while ((opt = getopt(argc, argv, "lwcm")) != -1)
    {
        switch (opt)
        {
            case 'l': {
                lines = true;
                break;
            }

            case 'w': {
                words = true;
                break;
            }

            case 'c': {
                bytes = true;
                break;
            }

            case 'm': {
                characters = true;
                break;
            }

            case '?': {
                throw std::runtime_error("Unknown flag: " +
                                         std::string(1, static_cast<char>(optopt)));
            }

            default:
                break;
        }
    }

    for (int i = optind; i < argc; i++)
    {
        fileNames.push_back(argv[i]);
    }

    if (!lines && !words && !bytes && !characters)
    {
        lines = words = bytes = true;
    }

    return {lines, words, bytes, characters, std::move(fileNames)};
}

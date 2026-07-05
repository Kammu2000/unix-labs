#include <fstream>
#include <iostream>
#include <optional>
#include <string_view>

#include "parser.hpp"
#include "wc_modern.hpp"

inline void logResult(const WcResult& result, const WcOptions& options,
                      std::optional<std::string_view> fileName)
{

    if (options.lines)
    {
        std::cout << result.lines << " ";
    }

    if (options.words)
    {
        std::cout << result.words << " ";
    }

    if (options.bytes)
    {
        std::cout << result.bytes << " ";
    }

    if (options.characters)
    {
        std::cout << result.characters << " ";
    }

    if (fileName.has_value())
    {
        std::cout << fileName.value() << " ";
    }

    std::cout << "\n";
}

int main(int argc, char* argv[])
{
    WcOptions options = parse(argc, argv);

    if (options.fileNames.size() == 0)
    {
        WcResult result = wc_modern(std::cin);
        logResult(result, options, std::nullopt);
        return 0;
    }

    for (auto& fileName : options.fileNames)
    {
        std::ifstream file(fileName);

        if (!file.is_open())
        {
            std::cerr << fileName << " could not be opened \n";
            continue;
        }

        WcResult result = wc_modern(file);
        logResult(result, options, fileName);
    }

    return 0;
}

#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "parser.hpp"
#include "tail_modern.hpp"

void printLineSeparator(std::string_view fileName)
{
    std::cout << "\n";
    std::cout << "==> " << fileName << " <==";
    std::cout << "\n";
}

int main(int argc, char* argv[])
{
    try
    {
        TailOptions args = parse(argc, argv);
        int totalFiles = (int)args.fileNames.size();

        if (totalFiles == 0)
        {
            tail(std::cin, args.count);
            return 0;
        }

        for (int i = 0; i < totalFiles; i++)
        {
            std::string fileName = args.fileNames[i];
            std::ifstream file(fileName);

            if (!file.is_open())
            {
                std::cerr << fileName << " cound not be opened \n";
                continue;
            }

            if (totalFiles > 1)
            {
                printLineSeparator(fileName);
            }

            tail(file, args.count);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}

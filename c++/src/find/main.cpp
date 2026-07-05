#include <exception>
#include <iostream>

#include "parser.hpp"
#include "find_modern.hpp"

int main(int argc, char* argv[])
{
    try
    {
        FindOptions options = parse(argc, argv);
        find_modern(options);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }

    return 0;
}

#include <cstddef>
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>

#include "parser.hpp"

void parse_type(FindOptions& options, const std::string_view& value)
{
    if (value == "f" or value == "d")
    {
        options.type = std::string(value) == "f" ? FileType::File : FileType::Directory;
    }
    else
    {
        throw std::runtime_error(std::format("Invalid filetype: {}", value));
    }
}

void parse_size(FindOptions& options, const std::string_view& value)
{
    SizeComparison comparator;
    std::string bytes_str;

    if (value.size() == 0)
    {
        throw std::runtime_error("Size argument cannot be empty");
    }

    if (value[0] == '+')
    {
        comparator = SizeComparison::Greater;
        bytes_str = value.substr(1);
    }
    else if (value[0] == '-')
    {
        comparator = SizeComparison::Less;
        bytes_str = value.substr(1);
    }
    else
    {
        comparator = SizeComparison::Equal;
        bytes_str = value.substr(0);
    }

    try
    {
        size_t bytes = std::stoull(bytes_str);
        options.size = {comparator, bytes};
    }
    catch (...)
    {
        throw std::runtime_error(std::format("Invalid size: {}", value));
    }
}

FindOptions parse(int argc, char* argv[])
{
    if (argc < 2)
    {
        throw std::runtime_error("No argument was provided");
    }

    FindOptions options;

    size_t start_idx = 1;
    std::string_view token = argv[++start_idx];

    auto assert_arg_size = [&argc, &token](size_t i) {
        if (i + 1 >= argc)
        {
            throw std::runtime_error(std::format("No value was provided for flag: {}", token));
        }
    };

    if (!token.starts_with("-"))
    {
        options.root = token;
    }

    for (size_t i = start_idx; i < argc; i++)
    {
        token = argv[i];

        if (!token.starts_with("-"))
        {
            throw std::runtime_error(std::format("Invalid flag: {}", token));
        }

        assert_arg_size(i);
        i++;
        std::string_view value = argv[i];

        if (token == "-type")
        {
            parse_type(options, value);
        }
        else if (token == "-name")
        {
            options.name_pattern = value;
        }
        else if (token == "-size")
        {
            parse_size(options, value);
        }
        else
        {
            throw std::runtime_error(std::format("Invalid flag: {}", token));
        }
    }

    return options;
}

#include <fnmatch.h>
#include <iostream>
#include <sys/stat.h>
#include <string>
#include <cstddef>

#include "find_modern.hpp"
#include "parser.hpp"

bool name_filter(const std::string& pattern, const std::string& name)
{
    return fnmatch(pattern.c_str(), name.c_str(), 0) == 0;
}

bool type_filter(const FileType& allowed_type, const FileType& type)
{
    if (allowed_type == FileType::Any)
    {
        return true;
    }

    return allowed_type == type;
}

bool size_filter(const fs::path& entity_path, const SizeFilter& size)
{
    struct stat buffer;
    lstat(entity_path.c_str(), &buffer);
    size_t entity_size = buffer.st_size;

    if (size.comparator == SizeComparison::Equal)
    {
        return entity_size == size.bytes;
    }
    else if (size.comparator == SizeComparison::Greater)
    {
        return entity_size > size.bytes;
    }
    else if (size.comparator == SizeComparison::Less)
    {
        return entity_size < size.bytes;
    }

    return false;
}

void find_modern(const FindOptions& options)
{
    for (const auto& entry : fs::recursive_directory_iterator(options.root))
    {
        auto entity_name = entry.path().filename().string();
        FileType type;

        if (fs::is_directory(entry.path()))
        {
            type = FileType::Directory;
        }
        else if (fs::is_regular_file(entry.path()))
        {
            type = FileType::File;
        }
        else
            continue;

        bool is_valid_type = type_filter(options.type, type);

        if (!is_valid_type)
        {
            continue;
        }

        bool is_valid_name = options.name_pattern.has_value()
                                 ? name_filter(options.name_pattern.value(), entity_name)
                                 : true;
        if (!is_valid_name)
        {
            continue;
        }

        bool is_valid_size =
            options.size.has_value() ? size_filter(entry.path(), options.size.value()) : true;

        if (!is_valid_size)
        {
            continue;
        }

        std::cout << entry.path().string() << "\n";
    }
}

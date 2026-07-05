#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <grp.h>
#include <iostream>
#include <pwd.h>
#include <string>
#include <sys/stat.h>
#include <utility>

#include "ls_modern.hpp"

void print_entry(const fs::path& entry_path, bool isLongListFormat)
{
    auto entry_name = std::move(entry_path.filename().string());

    if (!isLongListFormat)
    {
        std::cout << entry_name << "\t";
        return;
    }

    struct stat stat_buffer;

    if (stat(entry_path.c_str(), &stat_buffer) == -1)
    {
        perror("stat");
        return;
    }

    auto owner_name = std::move(std::string(getpwuid(stat_buffer.st_uid)->pw_name));
    auto group_name = std::move(std::string(getgrgid(stat_buffer.st_gid)->gr_name));
    auto hard_link_count = stat_buffer.st_nlink;
    auto entry_size = stat_buffer.st_size;
    auto last_modified_time = stat_buffer.st_mtimespec;

    std::cout << hard_link_count << "\t" << owner_name << "\t" << group_name << "\t" << entry_size
              << "\t" << last_modified_time.tv_nsec << "\t" << entry_name << "\n";
}

void ls_modern(const fs::path& dir_path, const LsFlags& options)
{

    auto isValid = [options](const std::string& entry_name) {
        if (entry_name.size() == 0)
        {
            return false;
        }

        if (entry_name[0] == '.' and !options.showHiddenFiles)
        {
            return false;
        }

        return true;
    };

    for (const auto& entry : fs::directory_iterator(dir_path))
    {
        auto entry_name = std::move(entry.path().filename().string());

        if (isValid(entry_name))
        {
            print_entry(entry.path(), options.isLongListFormat);
        }
    }

    std::cout << "\n";
}

#include <filesystem>
#include <optional>
#include <string>

namespace fs = std::filesystem;

enum class FileType
{
    Any,
    File,
    Directory,
};

enum class SizeComparison
{
    Equal,
    Less,
    Greater,
};

struct SizeFilter
{
    SizeComparison comparator;
    size_t bytes;
};

struct FindOptions
{
    fs::path root = ".";

    FileType type = FileType::Any;
    std::optional<std::string> name_pattern;
    std::optional<SizeFilter> size;
};

FindOptions parse(int argc, char* argv[]);

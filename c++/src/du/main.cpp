#include <cstdint>

#include "du_modern.hpp"
#include "parser.hpp"

int main(int argc, char* argv[])
{
    fs::path cwd = fs::current_path();
    DuOptions options = parse(argc, argv);
    uint32_t total = 0;

    for (const auto& dir_path : options.dir_paths)
    {
        total += du_modern(dir_path, options.flags);
    }

    if (options.flags.showTotal)
    {
        log_entity_data("total", total, options.flags.humanReadable);
    }

    return 0;
}

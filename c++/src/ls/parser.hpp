#pragma once

#include <filesystem>
#include <vector>
namespace fs = std::filesystem;

struct LsFlags {
  bool showHiddenFiles;
  bool longListingFormat;
};

struct LsOptions {
  LsFlags flags;
  std::vector<fs::path> dir_paths;
};

LsOptions parse(int argc, char *argv[]);

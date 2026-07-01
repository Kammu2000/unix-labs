#pragma once

#include <filesystem>
#include <vector>
namespace fs = std::filesystem;

struct DuFlags {
  bool humanReadable;
  bool showFiles;
  bool showTotal;
};

struct DuOptions {
  DuFlags flags;
  std::vector<fs::path> dir_paths;
};

DuOptions parse(int argc, char *argv[]);

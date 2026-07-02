#include <iostream>
#include <string>
#include <utility>

#include "ls_modern.hpp"

void ls_modern(const fs::path &dir_path, const LsFlags &options) {

  auto isValid = [options](const std::string &entry_name) {
    if (entry_name.size() == 0) {
      return false;
    }

    if (entry_name[0] == '.' and !options.showHiddenFiles) {
      return false;
    }

    return true;
  };

  for (const auto &entry : fs::directory_iterator(dir_path)) {
    std::string entry_name = std::move(entry.path().filename().string());

    if (isValid(entry_name)) {
      std::cout << entry_name << "\t";
    }
  }

  std::cout << "\n";
}

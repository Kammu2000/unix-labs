#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "grep.hpp"

void search_file(const fs::path &file_path, const std::string &pattern) {
  std::ifstream file(file_path);

  if (!file.is_open()) {
    throw std::runtime_error(file_path.string() + " cound not be opened");
  }

  std::string line;

  while (std::getline(file, line)) {
    if (line.find(pattern) != std::string::npos) {
      std::cout << file_path.string() << ": " << line << "\n";
    }
  }
}

void search_directory(const fs::path &dir_path, const std::string &pattern) {
  for (const auto &entity_path : fs::recursive_directory_iterator(dir_path)) {
    if (fs::is_directory(entity_path)) {
      search_directory(entity_path, pattern);
    } else {
      search_file(entity_path, pattern);
    }
  }
}

void grep(const GrepOptions &options) {
  for (const auto &entity_path : options.paths) {
    if (fs::is_directory(entity_path)) {
      if (!options.shouldRecurse) {
        std::cerr << entity_path.string() << ": is a directory \n";
        continue;
      }

      search_directory(entity_path, options.pattern);
      continue;
    }

    if (fs::is_regular_file(entity_path)) {
      search_file(entity_path, options.pattern);
      continue;
    }

    std::cerr << entity_path.string() << ": No such file or directory";
  }
}

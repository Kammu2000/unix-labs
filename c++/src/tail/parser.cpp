#include <stdexcept>
#include <string>
#include <vector>

#include "parser.hpp"

TailOptions parse(int argc, char *argv[]) {
  std::vector<std::string> fileNames;
  int count = 0;

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-n") {
      if (i + 1 < argc) {
        count = std::stoi(argv[++i]);
      } else {
        throw std::runtime_error("No value found after -n");
      }
    } else {
      fileNames.push_back(argv[i]);
    }
  }

  return {fileNames, count};
}

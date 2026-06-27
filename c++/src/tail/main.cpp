#include <exception>
#include <fstream>
#include <iostream>

#include "parser.hpp"
#include "tail_modern.hpp"

int main(int argc, char *argv[]) {
  try {
    TailOptions args = parse(argc, argv);

    if (args.fileNames.size() == 0) {
      tail(std::cin, args.count);
      return 0;
    }

    for (auto &fileName : args.fileNames) {
      std::ifstream file(fileName);

      if (!file.is_open()) {
        std::cerr << fileName << " cound not be opened \n";
        continue;
      }

      tail(file, args.count);
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}

#include <exception>
#include <fstream>
#include <iostream>

#include "head_modern.hpp"
#include "parser.hpp"

int main(int argc, char *argv[]) {
  try {
    HeadOptions args = parse(argc, argv);

    if (args.fileNames.size() == 0) {
      head(std::cin, args.count);
      return 0;
    }

    for (auto &fileName : args.fileNames) {
      std::ifstream file(fileName);

      if (!file.is_open()) {
        std::cerr << fileName
                  << " could not be opened because of some issue \n";
        continue;
      }

      head(file, args.count);
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}

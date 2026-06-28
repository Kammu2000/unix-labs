#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

#include "head_modern.hpp"
#include "parser.hpp"

void printLineSeparator(std::string_view fileName) {
  std::cout << "\n";
  std::cout << "==> " << fileName << " <==";
  std::cout << "\n\n";
}

int main(int argc, char *argv[]) {
  try {
    HeadOptions args = parse(argc, argv);
    int totalFiles = (int)args.fileNames.size();

    if (totalFiles == 0) {
      head(std::cin, args.count);
      return 0;
    }

    for (int i = 0; i < totalFiles; i++) {

      std::string fileName = args.fileNames[i];

      std::ifstream file(fileName);

      if (!file.is_open()) {
        std::cerr << fileName
                  << " could not be opened because of some issue \n";
        continue;
      }

      if (totalFiles > 1) {
        printLineSeparator(fileName);
      }

      head(file, args.count);
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}

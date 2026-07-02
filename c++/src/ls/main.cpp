#include <exception>
#include <iostream>

#include "ls_modern.hpp"
#include "parser.hpp"

int main(int argc, char *argv[]) {
  LsOptions options = parse(argc, argv);

  try {
    for (const auto &dir_path : options.dir_paths) {
      std::cout << dir_path.filename().string() << "\n";
      ls_modern(dir_path, options.flags);
      std::cout << "\n";
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << "\n";
  }

  return 0;
}

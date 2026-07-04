#include <exception>
#include <iostream>
#include <stdexcept>

#include "parser.hpp"

int main(int argc, char *argv[]) {
  try {
    GrepOptions options = parse(argc, argv);

    if (options.paths.empty()) {
      throw std::runtime_error("No path was provided in command");
    }

  } catch (std::exception &e) {
    std::cerr << e.what() << "\n";
  }

  return 0;
}

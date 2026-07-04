#include <exception>
#include <iostream>

#include "parser.hpp"
#include "xargs.hpp"

int main(int argc, char *argv[]) {
  try {
    XargsOption options = parse(argc, argv);
    xargs(options);
  } catch (std::exception &e) {
    std::cerr << e.what() << "\n";
  }
  return 0;
}

#include <iostream>

#include "head_modern.hpp"

void head(std::istream &readable_stream, int k) {
  std::string line;

  while (k > 0 and std::getline(readable_stream, line)) {
    std::cout << line << "\n";
    k--;
  }
}

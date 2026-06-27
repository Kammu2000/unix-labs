#include <iostream>
#include <queue>
#include <string>

#include "tail_modern.hpp"

void tail(std::istream &readable_stream, int k) {
  int threshold = k;
  std::string line;
  std::queue<std::string> q;

  while (k > 0 and std::getline(readable_stream, line)) {
    if (q.size() == threshold) {
      q.pop();
    }

    q.push(line);
    k--;
  }

  while (q.size()) {
    auto &temp = q.front();
    q.pop();

    std::cout << temp << "\n";
  }
}

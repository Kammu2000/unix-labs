#pragma once

#include <istream>

struct WcResult {
  int lines;
  int words;
  int bytes;
  int characters;
};

WcResult wc_modern(std::istream &readable_stream);

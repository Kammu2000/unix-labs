#pragma once

#include <string>
#include <vector>

struct WcOptions {
  bool lines;
  bool words;
  bool bytes;
  bool characters;
  std::vector<std::string> fileNames;
};

WcOptions parse(int argc, char *argv[]);

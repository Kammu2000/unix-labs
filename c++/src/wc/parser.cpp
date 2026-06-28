#include <string>
#include <unistd.h>
#include <vector>

#include "parser.hpp"

WcOptions parse(int argc, char *argv[]) {
  int opt;
  bool lines = false, words = false, bytes = false, characters = false;
  std::vector<std::string> fileNames;

  while ((opt = getopt(argc, argv, "lwcm")) != -1) {
    switch (opt) {
    case 'l': {
      lines = true;
      break;
    }

    case 'w': {
      words = true;
      break;
    }

    case 'c': {
      bytes = true;
      break;
    }

    case 'm': {
      characters = true;
      break;
    }

    default:
      break;
    }
  }

  for (int i = optind; i < argc; i++) {
    fileNames.push_back(argv[i]);
  }

  if (!lines && !words && !bytes && !characters) {
    lines = words = bytes = true;
  }

  return {lines, words, bytes, characters, std::move(fileNames)};
}

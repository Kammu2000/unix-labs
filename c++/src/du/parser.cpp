#include <stdexcept>
#include <unistd.h>
#include <vector>

#include "parser.hpp"

DuOptions parse(int argc, char *argv[]) {
  DuFlags flags = {
      .humanReadable = false, .showFiles = false, .showTotal = false};

  int opt;
  // set opterr to 0 to avoid silent error messages from getopt
  opterr = 0;

  while ((opt = getopt(argc, argv, "ahc")) != -1) {
    switch (opt) {
    case 'a': {
      flags.showFiles = true;
      break;
    }

    case 'h': {
      flags.humanReadable = true;
      break;
    }

    case 'c': {
      flags.showTotal = true;
      break;
    }

    case '?': {
      throw std::runtime_error("Unknown flag: " +
                               std::string(1, static_cast<char>(optopt)));
      break;
    }
    }
  }

  std::vector<fs::path> dir_paths;

  for (int i = optind; i < argc; i++) {
    dir_paths.push_back(argv[i]);
  }

  if (dir_paths.size() == 0) {
    dir_paths.push_back(".");
  }

  return {flags, dir_paths};
}

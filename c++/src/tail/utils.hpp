#pragma once

#include <cstdlib>
#include <stdexcept>
#include <string>

// Rationale: Inline function should only be in header file similar to templates
inline int parseInt(const char *s) {
  char *end = nullptr;
  long val = std::strtol(s, &end, 10);

  if (*end != '\0') {
    throw std::runtime_error("Invalid integer: " + std::string(s));
  }

  if (val < std::numeric_limits<int>::min() ||
      val > std::numeric_limits<int>::max()) {
    throw std::runtime_error("Integer out of range: " + std::string(s));
  }

  return static_cast<int>(val);
}

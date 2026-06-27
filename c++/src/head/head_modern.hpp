#pragma once

#include <istream>

// Note: istream is parent class of ifstream and all other readable streams
// inherit from it
void head(std::istream &readable_stream, int k);

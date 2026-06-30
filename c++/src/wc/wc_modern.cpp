#include <cctype>

#include "wc_modern.hpp"

WcResult wc_modern(std::istream &readable_stream) {
  int lines = 0, words = 0, bytes = 0, characters = 0;
  char ch;
  bool inWord = false;

  while (readable_stream.get(ch)) {
    bytes++;

    /* Solution Rationale for counting character (Unicode Point):
     UTF-8 has a nice property:
      Every Unicode character starts with a leading byte.
      Continuation bytes always start with:
      10xxxxxx
      So you only need to count bytes that are not continuation bytes.

      Example:
      😊
      UTF-8:

      11110000
      10011111
      10011000
      10001010

      Only the first byte starts a new character.
      The other three are continuation bytes.
    */
    unsigned char byte = static_cast<unsigned char>(ch);

    if ((~byte & 0b11000000) == 0) {
      characters++;
    }

    if (ch == '\n') {
      lines++;
    }

    if (std::isspace(static_cast<unsigned char>(ch))) {
      inWord = false;
    } else if (!inWord) {
      words++;
      inWord = true;
    }
  }

  if (bytes > 0 and ch != '\n') {
    lines++;
  }

  return {lines, words, bytes, characters};
}

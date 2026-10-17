#ifndef ALESSASTRUCT_CHARACTER_H
#define ALESSASTRUCT_CHARACTER_H

#include <cstddef>

static constexpr int TO_LOWER_SHIFT = 'a' - 'A';

static inline bool isDigitCharacter(char character) {
  return character >= '0' && character <= '9';
}

static inline bool isSpacingCharacter(char character) {
  switch (character) {
  case ' ':
  case '\n':
  case '\r':
  case '\t':
    return true;

  default:
    return false;
  }
}

static inline bool isUppercaseCharacter(char character) {
  return character >= 'A' && character <= 'Z';
}

inline bool isLowercaseCharacter(char character) {
  return character >= 'a' && character <= 'z';
}

static inline bool isAlphabeticalCharacter(char character) {
  return isUppercaseCharacter(character) || isLowercaseCharacter(character);
}

static inline char toLowerCharacter(char character) {
  return isUppercaseCharacter(character) ? character + TO_LOWER_SHIFT
                                         : character;
}

static inline char toDigitCharacter(size_t value) { return value + '0'; }

#endif // ALESSASTRUCT_CHARACTER_H

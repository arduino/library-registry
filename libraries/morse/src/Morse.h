#ifndef MORSE_H
#define MORSE_H

#include <Arduino.h>

// Morse lookup table entry
struct MorseMap {
  const char* code;
  char letter;
};

// Function to decode a Morse sequence into a character
char decodeMorse(const char* code);

#endif

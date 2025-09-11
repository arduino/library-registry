#include "Morse.h"

// Morse lookup table (A–Z, 0–9)
const MorseMap morseTable[] = {
  {".-", 'A'},   {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'},  {".", 'E'},
  {"..-.", 'F'}, {"--.", 'G'},  {"....", 'H'}, {"..", 'I'},   {".---", 'J'},
  {"-.-", 'K'},  {".-..", 'L'}, {"--", 'M'},   {"-.", 'N'},   {"---", 'O'},
  {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'},  {"...", 'S'},  {"-", 'T'},
  {"..-", 'U'},  {"...-", 'V'}, {".--", 'W'},  {"-..-", 'X'}, {"-.--", 'Y'},
  {"--..", 'Z'},

  {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'}, {"....-", '4'},
  {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'}
};

// Decode a Morse sequence into a character
char decodeMorse(const char* code) {
  for (unsigned int i = 0; i < sizeof(morseTable) / sizeof(morseTable[0]); i++) {
    if (strcmp(code, morseTable[i].code) == 0) {
      return morseTable[i].letter;
    }
  }
  return '?'; // Unknown sequence
}

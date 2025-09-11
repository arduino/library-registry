#include <Morse.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Morse Library Example");
  Serial.println("----------------------");

  // Decode a simple Morse sequence
  char letter = decodeMorse(".-"); // should return 'A'
  Serial.print("Decoded '.-': ");
  Serial.println(letter);

  letter = decodeMorse("..."); // should return 'S'
  Serial.print("Decoded '...': ");
  Serial.println(letter);

  letter = decodeMorse("----."); // should return '9'
  Serial.print("Decoded '----.': ");
  Serial.println(letter);

  // Unknown sequence
  letter = decodeMorse("..--.."); // not defined
  Serial.print("Decoded '..--..': ");
  Serial.println(letter); // should print '?'
}

void loop() {
  // Nothing here for now
}

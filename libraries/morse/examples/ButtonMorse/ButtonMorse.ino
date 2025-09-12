#include <Morse.h>

#define DOT_BUTTON 2
#define DASH_BUTTON 3

String currentCode = "";
unsigned long lastPressTime = 0;
const unsigned long letterGap = 1500;

void setup() {
  pinMode(DOT_BUTTON, INPUT_PULLUP);
  pinMode(DASH_BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(DOT_BUTTON) == LOW) {
    currentCode += ".";
    delay(300);
    lastPressTime = millis();
  }

  if (digitalRead(DASH_BUTTON) == LOW) {
    currentCode += "-";
    delay(300);
    lastPressTime = millis();
  }

  if (currentCode.length() > 0 && millis() - lastPressTime > letterGap) {
    char decoded = decodeMorse(currentCode.c_str());
    Serial.print(decoded);
    currentCode = "";
  }
}

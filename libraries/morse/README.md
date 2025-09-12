# Morse Arduino Library

A simple Arduino library for decoding Morse code.  
It provides a lookup table and functions to translate Morse sequences (`.` and `-`) into letters and numbers.  
Reusable across projects for IoT, communication experiments, and custom input devices.

---

## Features

- Decode Morse sequences (e.g. `".-" → A`).
- Supports **A–Z** and **0–9**.
- Lightweight: uses only a lookup table and string compare.
- Works on all Arduino boards (`architectures=*`).

---

## Installation

### Method 1: Arduino IDE Library Manager

_Not yet published to Library Manager – coming soon._

### Method 2: Manual Installation

1. Download or clone this repo:
   ```bash
   git clone https://github.com/aryankajiwala/Morse.git
   ```
2. Move the folder into your Arduino libraries folder:
   ```
   Documents/Arduino/libraries/Morse/
   ```
3. Restart Arduino IDE.
4. Include the library in your sketch:
   ```cpp
   #include <Morse.h>
   ```

---

## Usage

### Simple Test

```cpp
#include <Morse.h>

void setup() {
  Serial.begin(9600);

  char test = decodeMorse(".-"); // should return 'A'
  Serial.print("Decoded: ");
  Serial.println(test);
}

void loop() {
}
```

**Output:**

```
Decoded: A
```

---

## API Reference

### `char decodeMorse(const char* code)`

- **Input:** Morse sequence as `const char*` (e.g., `".-"`).
- **Output:** Corresponding ASCII character (`'A'`) or `'?'` if unknown.

---

## Roadmap

- [ ] Add **encoder function** (`encodeMorse('A') → ".-"`).
- [ ] Add support for **punctuation** (`. , ? !`).
- [ ] Publish to Arduino Library Manager.

---

## Author

**Aryan Kajiwala**  
📧 aryanbkaji124@gmail.com  
🔗 [GitHub](https://github.com/AryanKaji)

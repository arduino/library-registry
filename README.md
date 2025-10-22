# NikkiClientESP

**NikkiClientESP** is an Arduino library for **ESP32** that connects to the [Nikki.Build Playground](https://nikki.build) — a fun platform for ** rapid prototyping and applied learning ** using real IoT devices.

This library makes it easy for students, makers, and educators to connect their ESP32 boards to the Nikki Playground over **WebSocket (WSS)** and exchange data in real time.

---

## 🚀 Features

- Connect ESP32 to **Nikki Playground** securely via `wss://`
- Send and receive real-time data using JSON
- Auto-reconnect and status event callbacks
- Great for **IoT learning**, **STEM education**, and **rapid prototypes**

---

## 📦 Installation

### Option 1 — From Arduino Library Manager  
1. Open Arduino IDE  
2. Go to **Tools → Manage Libraries**  
3. Search for **"NikkiClientESP"**  
4. Click **Install**

### Option 2 — From GitHub  
1. Download this repo as ZIP  
2. In Arduino IDE, go to **Sketch → Include Library → Add .ZIP Library...**  
3. Select the downloaded ZIP file

---

## 🧩 Basic Example

```cpp
#include <WiFi.h>
#include <NikkiClientESP.h>

const char* WIFI_SSID = "YourWiFi";
const char* WIFI_PASS = "YourPassword";

const char* SERVICE_DEF_JSON = R"({

    // replace this line with  your serviceDef.json content here

})";

const char* SERVICE_TOKEN_JSON = R"({

    // replace this line with  your serviceDef.json content here

})";

NikkiClientESP nikki(SERVICE_DEF_JSON, SERVICE_TOKEN_JSON, true);

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  nikki.begin();
}

void loop() {
  nikki.loop();
  if (nikki.isConnected()) {
   
  if (nikki.isConnected()) {
    // Send a simple integer
    nikki.send(42);
    delay(5000);

    // Send a string
    nikki.send("Hello Nikki!");
    delay(5000);

    // Send a float
    nikki.send(23.7);
    delay(5000);

    // Send a JSON object
    DynamicJsonDocument doc(256);
    doc["temp"] = 27.3;
    doc["humidity"] = 62;
    doc["unit"] = "C";
    nikki.send(doc.as<JsonVariant>());

  }
    delay(5000);
  }
}

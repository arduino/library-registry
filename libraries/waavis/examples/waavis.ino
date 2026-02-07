// Example: Send a chat message using Waavis API

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "This example supports ESP8266 and ESP32 only."
#endif

#include <Waavis.h>

const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

const char *deviceToken = "DEVICE_TOKEN";
const char *destination = "628xxxxxx";

WaavisClient waavis;

void setup() {
	Serial.begin(115200);
	delay(200);

	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print('.');
	}
	Serial.println();
	Serial.println("WiFi connected");

	bool ok = waavis.sendChat(deviceToken, destination, "Halo");
	if (ok) {
		Serial.println("Message sent");
	} else {
		Serial.print("Send failed: ");
		Serial.println(waavis.lastError());
	}
}

void loop() {}

#include "Waavis.h"

#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>
#elif defined(ESP32)
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#else
#error "Waavis library supports ESP8266 and ESP32 only."
#endif

WaavisClient::WaavisClient(const String &baseUrl)
    : _baseUrl(baseUrl), _insecure(true), _lastError("") {}

void WaavisClient::setInsecure(bool insecure) {
  _insecure = insecure;
}

String WaavisClient::lastError() const {
  return _lastError;
}

bool WaavisClient::sendChat(const String &token, const String &to, const String &message) {
  if (WiFi.status() != WL_CONNECTED) {
    _lastError = "WiFi not connected";
    return false;
  }

  String url = _baseUrl + "/v1/send_chat?token=" + urlEncode(token) +
               "&to=" + urlEncode(to) +
               "&message=" + urlEncode(message);

#if defined(ESP8266)
  BearSSL::WiFiClientSecure client;
  if (_insecure) {
    client.setInsecure();
  }
  HTTPClient http;
  if (!http.begin(client, url)) {
    _lastError = "HTTP begin failed";
    return false;
  }
#elif defined(ESP32)
  WiFiClientSecure client;
  if (_insecure) {
    client.setInsecure();
  }
  HTTPClient http;
  if (!http.begin(client, url)) {
    _lastError = "HTTP begin failed";
    return false;
  }
#endif

  int httpCode = http.GET();
  if (httpCode <= 0) {
    _lastError = http.errorToString(httpCode);
    http.end();
    return false;
  }

  if (httpCode < 200 || httpCode >= 300) {
    _lastError = "HTTP " + String(httpCode);
    http.end();
    return false;
  }

  _lastError = "";
  http.end();
  return true;
}

String WaavisClient::urlEncode(const String &value) const {
  String encoded = "";
  const char *hex = "0123456789ABCDEF";
  for (size_t i = 0; i < value.length(); ++i) {
    char c = value.charAt(i);
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '.' || c == '~') {
      encoded += c;
    } else if (c == ' ') {
      encoded += "%20";
    } else {
      encoded += '%';
      encoded += hex[(c >> 4) & 0x0F];
      encoded += hex[c & 0x0F];
    }
  }
  return encoded;
}

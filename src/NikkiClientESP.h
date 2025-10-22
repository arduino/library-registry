#ifndef NIKKI_CLIENT_ESP_H
#define NIKKI_CLIENT_ESP_H

#include <WiFi.h>
#include <Arduino.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <ctype.h>

#define OUT_DATA_SIZE_SEGMENT_MAX_LIMIT 2048
#define OUT_DATA_SIZE_MAX_LIMIT 4096
#define QUERY_STRING_KEY "token"

// --- Structs ---
struct NikkiServiceDetails {
  String GuID;
  String servID;
  String instID;
  String name;
  String dispName;
};

struct NikkiTokenDetails {
  String sessionID;
  String secrete;
  String wsAddr;
  float rateLimit;
};

enum deviceConnectionStatus {
  Inactive,
  Active
};

// --- Main Class ---
class NikkiClientESP {
public:
  NikkiClientESP(const char *serviceDefJson, const char *serviceTokenJson);

  void begin();
  void loop();
  bool isConnected();
  bool send(JsonVariant data);

  void setOnStatus(void (*callback)(const String &, const String &));
  void setOnMessage(void (*callback)(const JsonVariant &));

private:
  NikkiServiceDetails _serviceDetails;
  NikkiTokenDetails _tokenDetails;
  unsigned long _rateLimitMs;
  unsigned long _lastSendMs;
  WebSocketsClient _webSocket;

  void (*_onStatus)(const String &, const String &);
  void (*_onMessage)(const JsonVariant &);

  // Internal helper methods
  void _fireStatus(const String &status, const String &details);
  String _urlEncode(const String &str);
  bool _parseConfigs(const char *serviceDefJson, const char *serviceTokenJson);
  String getWssHost(const String &fullWssUrl);
  String getWssPathSegment(const String &fullWssUrl);
  String _buildWsUrl();
  void _webSocketEvent(WStype_t type, uint8_t *payload, size_t length);
};

#endif  // NIKKI_CLIENT_ESP_H

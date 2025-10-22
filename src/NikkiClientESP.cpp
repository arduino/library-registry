#include "NikkiClientESP.h"

// --- Constructor ---
NikkiClientESP::NikkiClientESP(const char *serviceDefJson, const char *serviceTokenJson) {
  _onStatus = nullptr;
  _onMessage = nullptr;
  _lastSendMs = 0;
  _rateLimitMs = 2000;

  if (!_parseConfigs(serviceDefJson, serviceTokenJson)) {
    Serial.println("[Nikki] ERROR: Failed to parse configuration JSONs.");
  }

  _rateLimitMs = (unsigned long)(_tokenDetails.rateLimit * 1000.0);
}

// --- Begin ---
void NikkiClientESP::begin() {
  uint16_t port = 443;
  String path = "/";
  String host = getWssHost(_tokenDetails.wsAddr);
  path = _buildWsUrl();

  _fireStatus("connecting to playground", host);
  _webSocket.beginSSL(host.c_str(), port, path.c_str());

  _webSocket.onEvent([this](WStype_t type, uint8_t *payload, size_t length) {
    this->_webSocketEvent(type, payload, length);
  });

  _fireStatus("connecting", "Attempting connection.");
}

// --- Loop ---
void NikkiClientESP::loop() {
  _webSocket.loop();
}

// --- Is Connected ---
bool NikkiClientESP::isConnected() {
  return _webSocket.isConnected();
}

// --- Send Data ---
bool NikkiClientESP::send(JsonVariant data) {
  _fireStatus("Info", "Sending msg.");

  if (!isConnected()) {
    _fireStatus("error", "{\"error\":\"not_connected\"}");
    return false;
  }

  unsigned long now = millis();
  if (_rateLimitMs > 0 && (now - _lastSendMs) < _rateLimitMs) {
    _fireStatus("error", "Rate limit exceeded.");
    return false;
  }

  String inputString;
  if (data.isNull() || serializeJson(data, inputString) == 0) {
    Serial.println("[Nikki] ERROR: Invalid input data for send.");
    return false;
  }

  if (inputString.length() > OUT_DATA_SIZE_SEGMENT_MAX_LIMIT) {
    Serial.printf("[Nikki] ERROR: Input data segment size (%d) exceeds limit (%d)\n",
                  inputString.length(), OUT_DATA_SIZE_SEGMENT_MAX_LIMIT);
    _fireStatus("error", "Input data segment size exceeded.");
    return false;
  }

  DynamicJsonDocument outDoc(OUT_DATA_SIZE_MAX_LIMIT);
  JsonObject root = outDoc.to<JsonObject>();

  root["GuID"] = _serviceDetails.GuID;
  root["dispName"] = _serviceDetails.dispName;
  root["servID"] = _serviceDetails.servID;
  root["name"] = _serviceDetails.name;
  root["instID"] = _serviceDetails.instID;
  root["secrete"] = _tokenDetails.secrete;
  root["sessionID"] = _tokenDetails.sessionID;
  root["data"] = data;
  root["action"] = "sendMessage";

  String finalPayload;
  if (serializeJson(root, finalPayload) == 0) {
    Serial.println("[Nikki] ERROR: Final serialization failed.");
    return false;
  }

  if (finalPayload.length() > OUT_DATA_SIZE_MAX_LIMIT) {
    Serial.printf("[Nikki] ERROR: Final payload size (%d) exceeds max limit (%d)\n",
                  finalPayload.length(), OUT_DATA_SIZE_MAX_LIMIT);
    _fireStatus("error", "Final payload size exceeded.");
    return false;
  }

  _webSocket.sendTXT(finalPayload);
  _lastSendMs = now;
  return true;
}

// --- Set Callbacks ---
void NikkiClientESP::setOnStatus(void (*callback)(const String &, const String &)) {
  _onStatus = callback;
}
void NikkiClientESP::setOnMessage(void (*callback)(const JsonVariant &)) {
  _onMessage = callback;
}

// --- Fire Status ---
void NikkiClientESP::_fireStatus(const String &status, const String &details) {
  if (_onStatus) {
    _onStatus(status, details);
  }
}

// --- URL Encode ---
String NikkiClientESP::_urlEncode(const String &str) {
  String encoded = "";
  char buf[4];
  for (unsigned int i = 0; i < str.length(); i++) {
    char c = str[i];
    if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
      encoded += c;
    else if (c == ' ')
      encoded += '+';
    else {
      sprintf(buf, "%%%02X", (uint8_t)c);
      encoded += buf;
    }
  }
  return encoded;
}

// --- Parse Configs ---
bool NikkiClientESP::_parseConfigs(const char *serviceDefJson, const char *serviceTokenJson) {
  DynamicJsonDocument servDoc(512);
  if (deserializeJson(servDoc, serviceDefJson)) {
    Serial.println("Failed to parse serviceDef JSON");
    return false;
  }

  _serviceDetails.GuID = servDoc["GuID"].as<String>();
  _serviceDetails.servID = servDoc["servID"].as<String>();
  _serviceDetails.instID = servDoc["instID"].as<String>();
  _serviceDetails.name = servDoc["name"].as<String>();
  _serviceDetails.dispName = servDoc["dispName"].as<String>();

  DynamicJsonDocument tokenDoc(512);
  if (deserializeJson(tokenDoc, serviceTokenJson)) {
    Serial.println("Failed to parse serviceToken JSON");
    return false;
  }

  _tokenDetails.sessionID = tokenDoc["sessionID"].as<String>();
  _tokenDetails.secrete = tokenDoc["secrete"].as<String>();
  _tokenDetails.wsAddr = tokenDoc["wsAddr"].as<String>();
  _tokenDetails.rateLimit = tokenDoc["rateLimit"].as<float>();
  if (_tokenDetails.rateLimit == 0) _tokenDetails.rateLimit = 2.0;

  return true;
}

// --- Host and Path ---
String NikkiClientESP::getWssHost(const String &fullWssUrl) {
  if (!fullWssUrl.startsWith("wss://")) return "";
  String host = fullWssUrl.substring(6);
  int pathIndex = host.indexOf('/');
  if (pathIndex != -1) host = host.substring(0, pathIndex);
  return host;
}

String NikkiClientESP::getWssPathSegment(const String &fullWssUrl) {
  if (!fullWssUrl.startsWith("wss://")) return "/";
  String tempUrl = fullWssUrl.substring(6);
  int pathStartIndex = tempUrl.indexOf('/');
  return (pathStartIndex == -1) ? "/" : tempUrl.substring(pathStartIndex);
}

// --- Build URL ---
String NikkiClientESP::_buildWsUrl() {
  DynamicJsonDocument urlDoc(1024);
  JsonObject servDef = urlDoc["servDef"].to<JsonObject>();
  servDef["GuID"] = _serviceDetails.GuID;
  servDef["servID"] = _serviceDetails.servID;
  servDef["instID"] = _serviceDetails.instID;
  servDef["name"] = _serviceDetails.name;
  servDef["dispName"] = _serviceDetails.dispName;

  JsonObject token = urlDoc["token"].to<JsonObject>();
  token["sessionID"] = _tokenDetails.sessionID;
  token["secrete"] = _tokenDetails.secrete;
  token["wsAddr"] = _tokenDetails.wsAddr;
  token["rateLimit"] = _tokenDetails.rateLimit;

  String jsonString;
  serializeJson(urlDoc, jsonString);
  String encodedPayload = _urlEncode(jsonString);
  String segment = getWssPathSegment(_tokenDetails.wsAddr);

  return segment + "?" + QUERY_STRING_KEY + "=" + encodedPayload;
}

// --- WebSocket Event ---
void NikkiClientESP::_webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      _fireStatus("disconnected", "Connection closed.");
      break;
    case WStype_CONNECTED:
      _fireStatus("connected", "Successfully established connection.");
      break;
    case WStype_TEXT: {
      String rawMessage = String((char *)payload, length);
      Serial.println("input msg received:");
      Serial.println(rawMessage);

      DynamicJsonDocument inDoc(length + 1024);
      DeserializationError error = deserializeJson(inDoc, payload, length);
      if (error) {
        Serial.println("Failed to parse input msg");
        Serial.println(error.c_str());
        return;
      }

      JsonObject root = inDoc.as<JsonObject>();
      if (root.containsKey("data") && root["data"].is<JsonObject>()) {
        JsonVariant innerData = root["data"].as<JsonObject>()["data"];
        if (!innerData.isNull() && _onMessage) {
          _onMessage(root);
        }
      } else {
        Serial.println("Invalid payload received");
      }
      break;
    }
    default:
      break;
  }
}

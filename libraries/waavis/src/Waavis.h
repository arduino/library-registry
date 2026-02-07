#ifndef WAAVIS_H
#define WAAVIS_H

#include <Arduino.h>

class WaavisClient {
public:
  explicit WaavisClient(const String &baseUrl = "https://api.waavis.com");
  void setInsecure(bool insecure);
  bool sendChat(const String &token, const String &to, const String &message);
  String lastError() const;

private:
  String _baseUrl;
  bool _insecure;
  String _lastError;

  String urlEncode(const String &value) const;
};

#endif

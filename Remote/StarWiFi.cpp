#include "StarWiFi.hpp"

void StarWiFiClass::setup() {
  Serial.println("[WiFi] Clearing old WiFi...");
  WiFi.softAPdisconnect(true);
  WiFi.disconnect(true);
  Serial.println("[WiFi] Cleared!");

  long msec = millis();
  WiFi.mode(WIFI_STA);
  WiFi.begin(API_WIFI_SSID, API_WIFI_PASS);
  Serial.print("[WiFi] Connecting");
  int ticks = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
    if (ticks++ == 20) Serial.println();
  }
  Serial.printf("\n[WiFi] Connected after %d ms!\n", millis() - msec);
}

void StarWiFiClass::awaitConnection() {
  while (WiFi.status() != WL_CONNECTED)
    delay(1);
}


StarWiFiClass StarWiFi;

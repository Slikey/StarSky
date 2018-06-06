#include "StarWiFi.hpp"

void StarWiFiClass::setup() {
  Serial.println("[WiFi] Clearing old WiFi...");
  WiFi.softAPdisconnect(true);
  WiFi.disconnect(true);
  Serial.println("[WiFi] Cleared!");

  Serial.print("[WiFi] Starting AP...");
  WiFi.softAPConfig(IPAddress(API_LOCAL_IP), IPAddress(API_GATEWAY), IPAddress(API_SUBNET));
  WiFi.softAP(API_WIFI_SSID, API_WIFI_PASS);
  Serial.println(" done!");

  Serial.print("[WiFi] IP: ");
  Serial.println(WiFi.softAPIP());
}

StarWiFiClass StarWiFi;


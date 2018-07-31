#include "StarAPI.hpp"

void StarAPIClass::sendRequest() {
  StarWiFi.awaitConnection();
  Serial.printf("[API] Sending: %s...", request);
  udp.beginPacket(API_HOST, API_PORT);
  udp.write(request);
  udp.endPacket();
  Serial.println(" done!");
}

void StarAPIClass::requestIncBrightness(int val) {
  snprintf(request, 511, "brightness %d", val);
  sendRequest();
}

void StarAPIClass::requestToggle() {
  strcpy(request, "toggle");
  sendRequest();
}

void StarAPIClass::requestMode() {
  strcpy(request, "mode");
  sendRequest();
}

void StarAPIClass::requestButton(int val) {
  snprintf(request, 511, "button %d", val);
  sendRequest();
}

StarAPIClass StarAPI;

#include "StarAPI.hpp"

void StarAPIClass::setup() {
  Serial.printf("[StarAPI] Starting UDP listener on port %d...", API_UDP_PORT);
  udp.begin(API_UDP_PORT);
  Serial.println(" done!");
}

void StarAPIClass::loop() {
  int packet_size = udp.parsePacket();
  if (packet_size) {
#ifdef API_DEBUG
    Serial.printf("[StarAPI] Received %d bytes from %s, port %d\n", packet_size,
                  udp.remoteIP().toString().c_str(), udp.remotePort());
#endif
    int len = udp.read(packet, 511);
    if (len > 0) packet[len] = 0;
    handleRequest();
#ifdef API_DEBUG
    Serial.println();
#endif
  }
}

void StarAPIClass::handleRequest() {
#ifdef API_DEBUG
  Serial.printf("[StarAPI] Handling: %s\n", packet);
#endif
  if (strncmp(packet, "brightness ", 11) == 0) {
    handleBrightness();
  } else if (strncmp(packet, "toggle", 6) == 0) {
    handleToggle();
  } else if (strncmp(packet, "mode", 4) == 0) {
    handleMode();
  } else if (strncmp(packet, "button", 6) == 0) {
    handleButton();
  } else {
#ifdef API_DEBUG
    Serial.printf("[StarAPI] NO HANDLER: %s\n", packet);
#endif
  }
}

void StarAPIClass::handleBrightness() {
  const char* number = packet + 11;
  long num = strtol(number, NULL, 11);
  if (num < 0) {
    num = -(num * num);
  } else {
    num = num * num;
  }
  StarStorage.incBrightness(num);
}

void StarAPIClass::handleToggle() {
  bool enabled = StarStorage.isEnabled();
  enabled = enabled ? 0 : 1;
  StarStorage.setEnabled(enabled);
}

void StarAPIClass::handleMode() {
  StarStorage.incStarMode();
}

void StarAPIClass::handleButton() {
  const char* number = packet + 7;
  long num = strtol(number, NULL, 7);
  if (num == 0) {
    handleMode();
  }
}

StarAPIClass StarAPI;

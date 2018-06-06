#include "StarAPI.hpp"

void StarAPIClass::setup() {
  Serial.printf("[StarAPI] Starting UDP listener on port %d...", API_UDP_PORT);
  udp.begin(API_UDP_PORT);
  Serial.println(" done!");
}

void StarAPIClass::loop() {
  int packet_size = udp.parsePacket();
  if (packet_size) {
    Serial.printf("[StarAPI] Received %d bytes from %s, port %d\n", packet_size,
                  udp.remoteIP().toString().c_str(), udp.remotePort());
    int len = udp.read(packet, 511);
    if (len > 0) packet[len] = 0;
    handleRequest();
    Serial.println();
  }
}

void StarAPIClass::handleRequest() {
  Serial.printf("[StarAPI] Handling: %s\n", packet);
  if (strncmp(packet, "brightness ", 11) == 0) {
    handleBrightness();
  } else if (strncmp(packet, "toggle", 6) == 0) {
    handleToggle();
  } else {
    Serial.printf("[StarAPI] NO HANDLER: %s\n", packet);
  }
}

void StarAPIClass::handleBrightness() {
  const char* number = packet + 11;
  long num = strtol(number, NULL, 11);
  StarStorage.incBrightness(num);
}

void StarAPIClass::handleToggle() {
  bool enabled = StarStorage.isEnabled();
  enabled = enabled ? 0 : 1;
  StarStorage.setEnabled(enabled);
}

StarAPIClass StarAPI;

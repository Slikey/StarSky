#pragma once

#include "config.h"
#include "packet.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

uint8_t api_local_mac[6] {WIFI_MAC};
WiFiUDP api_udp;

void api_setup() {
#ifdef WIFI_AP_RESET_ON_BOOT
  Sprintln("[WIFI] Clearing old WiFi...");
  WiFi.softAPdisconnect(true);
  WiFi.disconnect(true);
  Sprintln("[WIFI] Cleared!");
#endif

  Sprint("[WIFI] Mac: ");
  for (uint8_t i = 0; i < 6; ++i) {
    Sprint(api_local_mac[i], HEX);
    if (i != 5) Sprint(":");
  }
  Sprintln();
  wifi_set_macaddr(STATION_IF, api_local_mac);

  WiFi.persistent(false);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_AP_SSID, WIFI_AP_PASSWORD);

  wifi_set_macaddr(STATION_IF, api_local_mac);
}

void api_send_packet(starsky_packet_t *packet) {
  if (!packet_has_value(packet)) return;
  api_udp.beginPacket(IPAddress(WIFI_AP_LOCAL_IP), WIFI_UDP_PORT);
  api_udp.write((uint8_t*) packet, sizeof(starsky_packet_t));
  api_udp.endPacket();
}

void api_loop(uint32_t msec) {
  starsky_packet_t packet;
  uint8_t *p = (uint8_t *) &packet;
  for (uint8_t i = 0; i < sizeof(packet); ++i) {
    p[i] = rand();
  }
  api_send_packet(&packet);
}

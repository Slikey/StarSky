#pragma once

#include "config.h"
#include "packet.h"
#include "store.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

static uint8_t api_local_mac[6] = {WIFI_MAC};
static WiFiUDP api_udp;
static starsky_packet_t api_packet;

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
  wifi_set_macaddr(SOFTAP_IF, api_local_mac);

  WiFi.persistent(false);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(IPAddress(WIFI_AP_LOCAL_IP),
                    IPAddress(WIFI_AP_GATEWAY),
                    IPAddress(WIFI_AP_SUBNET_MASK));
  WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASSWORD, WIFI_CHANNEL, true, WIFI_AP_MAX_CONNECTIONS);
  Sprint("[WIFI] IP: "); Serial.println(WiFi.softAPIP());

  Sprintf("[WIFI] Starting UDP on port %d\n", WIFI_UDP_PORT);
  api_udp.begin(WIFI_UDP_PORT);
}

static void api_handle_packet() {
  storage_inc_brightness(api_packet.brightness_change);
  if (api_packet.toggle_enabled) storage_toggle_enabled();
  if (api_packet.inc_starmode) storage_inc_starmode(1);
  if (api_packet.enable_nightmode) {
    storage_set_enabled(true);
    storage_set_brightness(20);
  }
}

void api_loop(const uint32_t msec) {
  uint16_t packet_size;
  while (packet_size = api_udp.parsePacket()) {
#ifdef WIFI_PACKET_DUMP
    Sprintf("[WIFI] Received %d bytes from %s, port %d\n", packet_size,
            api_udp.remoteIP().toString().c_str(), api_udp.remotePort());
#endif
    api_udp.read((uint8_t *) &api_packet, sizeof(api_packet));
    api_handle_packet();
  }
}


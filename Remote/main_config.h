#pragma once

#define SERIAL_BAUD 2000000

#define WIFI_RESET_ON_BOOT
#define WIFI_AP_SSID "Sternhimmel-AP"
#define WIFI_AP_PASSWORD "password"
#define WIFI_AP_MAX_CONNECTIONS 4
#define WIFI_AP_LOCAL_IP 192,168,4,1
#define WIFI_AP_GATEWAY 192,168,4,0
#define WIFI_AP_SUBNET_MASK 255,255,255,0
#define WIFI_CHANNEL 5
#define WIFI_UDP_PORT 4210
#define WIFI_PACKET_DUMP

#ifdef SERIAL_ENABLED
#define Sprintln(...) (Serial.println(__VA_ARGS__))
#define Sprint(...) (Serial.print(__VA_ARGS__))
#define Sprintf(...) (Serial.printf(__VA_ARGS__))
#define Sbegin(a) (Serial.begin(a))
#else
#define Sprintln(...)
#define Sprint(...)
#define Sprintf(...)
#define Sbegin(a)
#endif
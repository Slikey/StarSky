#pragma once

#define API_DEBUG
#define API_WIFI_SSID "Sternhimmel-API"
#define API_WIFI_PASS "f8d3d686385ffd4a07e216625fb048f0"
#define API_LOCAL_IP 192,168,4,1
#define API_GATEWAY 192,168,4,254
#define API_SUBNET 255,255,255,0
#define API_UDP_PORT 3244

#define STORAGE_DELAY (5 * 1000)
#define STORAGE_EEPROM_SIZE 64

#define LIGHT_DOTS_COLOR NeoGrbwFeature
#define LIGHT_DOTS_METHOD Neo800KbpsMethod
#define LIGHT_DOTS_NUM_LEDS 100
#define LIGHT_DOTS_BRIGHTNESS 255
#define LIGHT_DOTS_DATA_PIN 18
#define LIGHT_BACKLIGHT_PIN 5
#define LIGHT_BACKLIGHT_CHANNEL 0
// PIN 5 = Onboard LED
#define LIGHT_MAIN_PIN A5


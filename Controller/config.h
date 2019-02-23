#pragma once

#define SERIAL_ENABLED
#include "main_config.h"

#define WIFI_MAC 0x61, 0xF1, 0x0E, 0xA9, 0x5C, 0x0A

#define EEPROM_ENABLED
#define EEPROM_CHECKSUM 35826622
#define EEPROM_SAVE_DELAY 10000

#define LED_BRIGHTNESS_MIN -10
#define LED_BRIGHTNESS_MAX 110

#define LIGHT_STARS_COLOR NeoGrbwFeature
#define LIGHT_STARS_METHOD Neo800KbpsMethod
#define LIGHT_STARS_NUM 145
#define LIGHT_STARS_BRIGHTNESS 255

<<<<<<< HEAD
#define LIGHT_BACKLIGHT_PIN D4

#define LIGHT_SPOTS_PIN D3
=======
#define LIGHT_BACKLIGHT_PIN D5

#define LIGHT_SPOTS_PIN D4
>>>>>>> 3307d50... More changes

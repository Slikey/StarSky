#pragma once

#include "config.h"
#include <NeoPixelBus.h>

#define LED_ARRAY_STARS 0
#define LED_ARRAY_HELLO_KITTY 1
#define LED_ARRAY_PONY 2
#define LED_ARRAY_SUNFLOWER 3
#define LED_ARRAY_PIKA 4
#define LED_ARRAY_HEART 5

struct starmode_t {
  uint32_t update_interval;
  void (*setup)();
  void (*loop)(uint32_t);
  RgbwColor (*color)(uint16_t);
};

uint8_t led_type[LIGHT_STARS_NUM];

void light_array_setup() {
  uint8_t *a = led_type;
  for (uint16_t i = 0; i < LIGHT_STARS_NUM; ++i) a[i] = LED_ARRAY_STARS;
  for (uint16_t i = 3; i <= 6; ++i) a[i] = LED_ARRAY_HELLO_KITTY;
  a[19] = a[20] = a[21] = a[23] = a[25] = a[26] = a[27] = a[28] = LED_ARRAY_PONY;
  a[56] = a[57] = a[59] = a[63] = a[65] = a[66] = a[68] = a[69] = a[70] = a[71] = a[74] = a[75] = a[76] = a[77] = a[78] = LED_ARRAY_SUNFLOWER;
  a[85] = a[86] = a[87] = a[89] = a[96] = a[98] = a[101] = a[108] = a[109] = a[110] = LED_ARRAY_PIKA;
  a[125] = LED_ARRAY_HEART;
}

uint8_t light_array_get(uint16_t idx) {
  return led_type[idx];
}

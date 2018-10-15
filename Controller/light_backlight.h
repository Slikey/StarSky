#pragma once

#include "config.h"
#include "store.h"
#include "light_array.h"
#include <NeoPixelBus.h>

static struct light_backlight_t {
  uint8_t value;
} light_backlight;

void light_backlight_setup() {
  Sprintf("[LightBacklight] Pin: %d\n", LIGHT_SPOTS_PIN);
  pinMode(LIGHT_BACKLIGHT_PIN, OUTPUT);
}

void light_backlight_loop(uint32_t msec) {
  int newValue = 0;
  if (storage_is_enabled()) {
    int brightness = storage_get_brightness();
    if (brightness > 100) brightness = 100;
    if (brightness < 0) brightness = 0;
    float val = (float) brightness / 100.0;
    newValue = (int) (val * 255);
  }
  if (light_backlight.value != newValue) {
    analogWrite(LIGHT_BACKLIGHT_PIN, newValue);
    Sprintf("[LightBacklight] Set backlight level from %d to %d.\n", light_backlight.value, newValue);
    light_backlight.value = newValue;
  }
}

#pragma once

#include "config.h"
#include "store.h"

static struct light_spots_t {
  bool value;
} light_spots;

void light_spots_setup() {
  Sprintf("[LightSpots] Pin: %d\n", LIGHT_SPOTS_PIN);
  pinMode(LIGHT_SPOTS_PIN, OUTPUT);
}

void light_spots_loop(const uint32_t msec) {
  int newValue = LOW;
  if (storage_is_enabled() && storage_get_brightness() > 100) {
    newValue = HIGH;
  }
  if (light_spots.value != newValue) {
    light_spots.value = newValue;
    digitalWrite(LIGHT_SPOTS_PIN, newValue);
    Sprintf("[LightSpots] Value: %s\n", newValue == HIGH ? "ON" : "OFF");
  }
}


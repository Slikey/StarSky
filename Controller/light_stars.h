#pragma once

#include "config.h"
#include "store.h"
#include "light_array.h"
#include <NeoPixelBus.h>

struct light_stars_t {
  uint32_t last_update;
  bool last_enabled;
  NeoPixelBus<LIGHT_STARS_COLOR, LIGHT_STARS_METHOD> *strip;
  starmode_t **modes;
  uint8_t modes_c;
} light_stars;

void light_stars_setup(starmode_t **modes, uint8_t modes_c) {
  Sprintln("[LightStars] Pin: RX");
  light_stars.strip = new NeoPixelBus<LIGHT_STARS_COLOR, LIGHT_STARS_METHOD>(LIGHT_STARS_NUM);
  light_stars.last_update = millis();
  light_stars.last_enabled = storage_is_enabled();
  light_stars.modes = modes;
  light_stars.modes_c = modes_c;
  for (uint8_t i = 0; i < modes_c; ++i) {
    modes[i]->setup();
  }
  light_stars.strip->Begin();
}

void light_stars_loop(uint32_t msec) {
  if (light_stars.modes_c == 0) return;
  if (storage_is_enabled()) {
    if (!light_stars.last_enabled)
      Sprintln("[LightStars] Enabled");
    // select star mode and reset if out of bounds
    uint8_t mode_idx = storage_get_starmode();
    if (mode_idx >= light_stars.modes_c)
      storage_set_starmode(mode_idx = 0);
    starmode_t *mode = light_stars.modes[mode_idx];

    // handle update interval and prevent 32bit overflow
    const uint32_t next_update = light_stars.last_update + mode->update_interval;
    if (next_update <= light_stars.last_update || next_update < msec) {
      mode->loop(msec);
      for (uint16_t i = 0; i < LIGHT_STARS_NUM; ++i)
        light_stars.strip->SetPixelColor(i, mode->color(i));
      light_stars.last_update = msec;
    }
    light_stars.strip->Show(); // this calls noInterrupts internally

    light_stars.last_enabled = true;
  }
  // turn off everything if we switch from enabled to disabled
  else if (light_stars.last_enabled) {
    Sprintln("[LightStars] Disabled");
    for (uint16_t i = 0; i < LIGHT_STARS_NUM; ++i) {
      light_stars.strip->SetPixelColor(i, 0);
    }
    light_stars.strip->Show(); // this calls noInterrupts internally

    light_stars.last_enabled = false;
  }
}


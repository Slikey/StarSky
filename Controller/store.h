#pragma once

#include "config.h"
#include <EEPROM.h>

static struct storage_data_t {
  uint32_t checksum;
  int8_t brightness;
  uint8_t starmode;
  uint8_t enabled;
  uint32_t mod_count; // used to determine if the store needs to be changed
} data;
static bool initialized;
static bool changed;
static uint32_t last_update;

static void mark_changed() {
  changed = true;
  last_update = millis();
  ++data.mod_count;
}

uint8_t storage_get_brightness() {
  return data.brightness;
}

void storage_set_brightness(int8_t brightness) {
  if (brightness < LED_BRIGHTNESS_MIN) brightness = LED_BRIGHTNESS_MIN;
  else if (brightness > LED_BRIGHTNESS_MAX) brightness = LED_BRIGHTNESS_MAX;
  if (brightness == data.brightness) return;
  Sprintf("[Storage] Brightness changed from %d to %d\n", data.brightness, brightness);
  data.brightness = brightness;
  mark_changed();
}

uint8_t storage_is_enabled() {
  return data.enabled;
}

void storage_set_enabled(uint8_t enabled) {
  if (enabled == data.enabled) return;
  data.enabled = enabled;
  Sprintf("[Storage] Set Enabled to %s\n", enabled ? "true" : "false");
  mark_changed();
}

uint8_t storage_get_starmode() {
  return data.starmode;
}

void storage_set_starmode(uint8_t starmode) {
  if (starmode == data.starmode) return;
  Sprintf("[Storage] StarMode changed from %d to %d\n", data.starmode, starmode);
  data.starmode = starmode;
  mark_changed();
}

void storage_inc_brightness(int8_t val) {
  if (val == 0) return;
  storage_set_brightness(storage_get_brightness() + val);
}

void storage_toggle_enabled() {
  storage_set_enabled(!storage_is_enabled());
}

void storage_inc_starmode(uint8_t modes) {
  storage_set_starmode(storage_get_starmode() + modes);
}

void storage_setup() {
#ifdef EEPROM_ENABLED
  Sprint("[Storage] Loading EEPROM...");
  EEPROM.begin(sizeof(data));
  EEPROM.get(0, data);
  Sprintln(" done!");

  last_update = 0;
  if (data.checksum == EEPROM_CHECKSUM) {
    changed = false;
    data.mod_count = 0; // we override modcount to start fresh,
  } else {
    Sprintln("[Storage] Checksum mismatch. Resetting EEPROM.");
    data.checksum = EEPROM_CHECKSUM;
    data.brightness = 20;
    data.starmode = 0;
    data.enabled = true;
    data.mod_count = 0;
    mark_changed();
  }
#endif
}

void storage_loop(uint32_t msec) {
#ifdef EEPROM_ENABLED
  if (!changed) return;
  uint32_t next_update = last_update + EEPROM_SAVE_DELAY;
  // check if timeout overflows OR timeout elapsed
  if (last_update > next_update || next_update > msec) return;

  int8_t brightness = storage_get_brightness();
  if (brightness > 100) {
    storage_set_brightness(LED_BRIGHTNESS_MAX);
  } else if (data.brightness <= 0) {
    storage_set_brightness(LED_BRIGHTNESS_MIN);
  }

  EEPROM.put(0, data);
  EEPROM.commit();
  Sprintf("[Storage] Wrote %d bytes.\n", sizeof(data));
  changed = false;
#endif
}


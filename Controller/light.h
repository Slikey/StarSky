#pragma once

#include "config.h"
#include "light_array.h"
#include "light_stars.h"
#include "light_backlight.h"
#include "light_spots.h"
#include "light_modes.h"

void light_setup() {
  light_modes_setup();  
  light_array_setup();
  light_stars_setup(starmode_modes);
  light_backlight_setup();
  light_spots_setup();
}

void light_loop(uint32_t msec) {
  light_stars_loop(msec);
  light_backlight_loop(msec);
  light_spots_loop(msec);
}


#pragma once

#include "light_array.h"
#include <NeoPixelBus.h>

//
// Rainbow Mode
//

struct mode_rainbow_t {
  starmode_t mode;
  uint8_t hue;
} mode_rainbow;

void mode_rainbow_setup() {
  mode_rainbow.mode.update_interval = 50;
  mode_rainbow.hue = 0;
}

void mode_rainbow_loop(uint32_t msec) {
  mode_rainbow.hue++;
}

RgbwColor mode_rainbow_color(uint16_t index) {
  if (light_array_get(index) == LED_ARRAY_STARS) {
    const float part = (float) index / (LIGHT_STARS_NUM - 1);
    const float offset = (float) mode_rainbow.hue / 0xFF;
    return HsbColor(part + offset, 1.0f, 1.0f);
  } else {
    return RgbwColor(0, 0, 0, 0xFF);
  }
}

//
// Sparkle Mode
//

struct sparkle_t {
  float from, to;
  uint8_t ticks, duration;
};

struct mode_sparkle_t {
  starmode_t mode;
  sparkle_t led[LIGHT_STARS_NUM];
} mode_sparkle;

void mode_sparkle_reset(sparkle_t *p) {
  p->from = p->to;
  p->to = random(0xFF);
  p->ticks = 0;
  p->duration = random(0x9F) + 0x5F;
}

void mode_sparkle_setup() {
  for (uint16_t i = 0; i < LIGHT_STARS_NUM; ++i) {
    sparkle_t *p = mode_sparkle.led + i;
    p->from = random(0xFF);
    p->to = random(0xFF);
    p->duration = random(0x9F) + 0x5F;
    p->ticks = 0;
  }
}

void mode_sparkle_loop(uint32_t msec) {
  for (uint16_t i = 0; i < LIGHT_STARS_NUM; ++i) {
    sparkle_t *p = mode_sparkle.led + i;
    if (++p->ticks > p->duration) {
      mode_sparkle_reset(p);
    }
  }
}

RgbwColor mode_sparkle_color(uint16_t index) {
  sparkle_t *p = mode_sparkle.led + index;
  float progress = (float) p->ticks / p->duration;
  float brightness = (p->to - p->from) * progress + p->from;
  uint8_t val = (uint8_t) brightness;
  return RgbwColor(0, 0, 0, val);
}

// 
// Bake
//

starmode_t *starmode_modes[2];

void light_modes_setup() {
  starmode_t *mode;
  
  mode = (starmode_t *) &mode_rainbow;
  mode->setup = mode_rainbow_setup;
  mode->loop = mode_rainbow_loop;
  mode->color = mode_rainbow_color;
  starmode_modes[0] = mode;
  
  mode = (starmode_t *) &mode_sparkle;
  mode->setup = mode_sparkle_setup;
  mode->loop = mode_sparkle_loop;
  mode->color = mode_sparkle_color;
  starmode_modes[1] = mode;
}


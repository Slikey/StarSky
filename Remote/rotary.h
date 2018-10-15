#pragma once

#include "config.h"

struct rotary_t {
  bool state;
  bool last_state;
  int8_t value;
} rotary;

void rotary_setup() {
  pinMode(ROTARY_PIN_1, INPUT);
  pinMode(ROTARY_PIN_2, INPUT);
  rotary.value = 0;
}

int8_t rotary_consume() {
  int8_t result = rotary.value;
  rotary.value = 0;
  return result;
}

void rotary_loop(uint32_t msec) {
  rotary.state = digitalRead(ROTARY_PIN_1);
  if (rotary.state != rotary.last_state) {
    if (digitalRead(ROTARY_PIN_2) != rotary.state) {
      --rotary.value;
    } else {
      ++rotary.value;
    }
    rotary.last_state = rotary.state;
  }
}


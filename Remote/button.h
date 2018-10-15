#pragma once

#include "config.h"

struct button_t {
  uint8_t pin;
  bool pressed;
  bool state;
  bool last_state;
  uint32_t next_time;
};

static button_t button_left;
static button_t button_right;
static button_t button_rotary;

static void button_init(button_t *button, uint8_t pin) {
  button->pin = pin;
  pinMode(pin, INPUT);
  button->last_state = digitalRead(pin);
  button->state = 0;
  button->next_time = 0;
}

void button_setup() {
  button_init(&button_left, BUTTON_LEFT_PIN);
  button_init(&button_right, BUTTON_RIGHT_PIN);
  button_init(&button_rotary, BUTTON_ROTARY_PIN);
}

static bool button_get(button_t* button) {
  bool result = button->pressed;
  button->pressed = 0;
  return result;
}

bool button_consume_left() {
  return button_get(&button_left);
}

bool button_consume_right() {
  return button_get(&button_right);
}

bool button_consume_rotary() {
  return button_get(&button_rotary);
}

static void button_handle(uint32_t msec, button_t *button) {
  if (button->next_time > msec) return;
  button->state = digitalRead(button->pin);
  if (button->state != button->last_state) {
    if (button->state) button->pressed = true;
    button->last_state = button->state;
    button->next_time = msec + 500;
  }
}

void button_loop(uint32_t msec) {
  button_handle(msec, &button_left);
  button_handle(msec, &button_right);
  button_handle(msec, &button_rotary);
}

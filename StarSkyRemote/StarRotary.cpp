#include "StarRotary.hpp"

void StarRotaryClass::setup() {
  Serial.print("[Rotary] Setup...");
  pinMode(ROTARY_1_PIN, INPUT);
  pinMode(ROTARY_2_PIN, INPUT);
  pinMode(ROTARY_BUTTON_PIN, INPUT_PULLUP);

  rotLastState = digitalRead(ROTARY_1_PIN);
  btnLastState = digitalRead(ROTARY_BUTTON_PIN);
  rotValue = 0;
  btnValue = 0;
  Serial.println(" done!");
}

void StarRotaryClass::loop() {
  btnState = !digitalRead(ROTARY_BUTTON_PIN);
  if (btnState != btnLastState) {
    btnValue = btnState;
    btnLastState = btnState;
  }

  rotState = digitalRead(ROTARY_1_PIN);
  if (rotState != rotLastState) {
    if (digitalRead(ROTARY_2_PIN) != rotState) {
      --rotValue;
    } else {
      ++rotValue;
    }
    rotLastState = rotState;
  }
}

int StarRotaryClass::getAndResetTicks() {
  int res = rotValue;
  rotValue = 0;
  return res;
}

bool StarRotaryClass::getAndResetButton() {
  bool res = btnValue;
  btnValue = 0;
  return res;
}

StarRotaryClass StarRotary;


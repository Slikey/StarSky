#include "StarButton.hpp"

void StarButtonClass::setup() {
  Serial.print("[Button] Setup...");
  pinMode(BUTTON_LEFT_PIN, INPUT);
  pinMode(BUTTON_RIGHT_PIN, INPUT);

  btnLeftLastState = digitalRead(BUTTON_LEFT_PIN);
  btnRightLastState = digitalRead(BUTTON_RIGHT_PIN);
  btnLeftState = 0;
  btnRightState = 0;
  Serial.println(" done!");
}

void StarButtonClass::loop() {
  btnLeftState = !digitalRead(BUTTON_LEFT_PIN);
  if (btnLeftState != btnLeftLastState) {
    if (btnLeftState) btnLeftPressed = true;
    btnLeftLastState = btnLeftState;
  }

  btnRightState = !digitalRead(BUTTON_RIGHT_PIN);
  if (btnRightState != btnRightLastState) {
    if (btnRightState) btnRightPressed = true;
    btnRightLastState = btnRightState;
  }
}
    
bool StarButtonClass::getAndResetLeftButton() {
  bool res = btnLeftPressed;
  btnLeftPressed = 0;
  return res;
}

bool StarButtonClass::getAndResetRightButton() {
  bool res = btnRightPressed;
  btnRightPressed = 0;
  return res;
}

StarButtonClass StarButton;


#pragma once

#include "config.h"

class StarButtonClass {
  private:
    bool btnLeftPressed, btnRightPressed;
    bool btnLeftState, btnRightState;
    bool btnLeftLastState, btnRightLastState;
    long btnLeftLastTime, btnRightLastTime;
  public:
    void setup();
    void loop();
    bool getAndResetLeftButton();
    bool getAndResetRightButton();
};

extern StarButtonClass StarButton;

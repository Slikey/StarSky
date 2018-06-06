#ifndef ROTARY_HEADER
#define ROTARY_HEADER

#include "config.h"

class StarRotaryClass {
  private:
    int rotState, rotLastState;
    int btnState, btnLastState;
    int rotValue;
    bool btnValue;
  public:
    void setup();
    void loop();
    int getAndResetTicks();
    bool getAndResetButton();
};

extern StarRotaryClass StarRotary;

#endif

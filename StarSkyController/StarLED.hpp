#ifndef STAR_LED_HEADER
#define STAR_LED_HEADER

#include "config.h"
#include <SPI.h>
#include <FastLED.h>

class StarLEDClass {
  private:
    SPISettings settings;
    void startBlock();
    void endBlock();
  public:
    void setup();
    void loop();
};

extern StarLEDClass StarLED;

#endif

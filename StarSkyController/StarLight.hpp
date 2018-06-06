#ifndef STAR_LIGHT_HEADER
#define STAR_LIGHT_HEADER

#include "config.h"
#include "StarStorage.hpp"
#include <FastLED.h>
#include "FastLED_RGBW.hpp"

class StarLightClass {
  private:
    CRGBW leds[LIGHT_DOTS_NUM_LEDS];
    CRGB *ledsRGB = (CRGB *) leds;
    int lastModCount;
    long lastStarColorUpdate;

    void starColor();
  public:
    void setup();
    void loop();
};

extern StarLightClass StarLight;

#endif

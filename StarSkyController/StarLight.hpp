#ifndef STAR_LIGHT_HEADER
#define STAR_LIGHT_HEADER

#include "config.h"
#include "StarStorage.hpp"
#include <FastLED.h>
#include "FastLED_RGBW.hpp"

class StarLightDotsClass {
  private:
    CRGBW leds[LIGHT_DOTS_NUM_LEDS];
    CRGB *ledsRGB = (CRGB *) leds;
    long lastStarColorUpdate;
  public:
    void setup();
    void loop();
    void starColor();
};

class StarLightBacklightClass {
  public:
    void setup();
    void loop();
};

class StarLightMainClass {
  public:
    void setup();
    void loop();
};

class StarLightClass {
  private:
    StarLightDotsClass dots;
    StarLightBacklightClass backlight;
    StarLightMainClass main;
    int lastModCount;

  public:
    void setup();
    void loop();
};

extern StarLightClass StarLight;

#endif

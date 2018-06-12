#pragma once

#include "config.h"
#include "StarStorage.hpp"
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

class StarLightDotsClass {
  private:
    long lastStarColorUpdate;
    bool lastEnabled;
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(LIGHT_DOTS_NUM_LEDS, LIGHT_DOTS_DATA_PIN, NEO_GRB + NEO_KHZ400);
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

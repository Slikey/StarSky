#pragma once

#include "config.h"
#include "StarStorage.hpp"

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

class StarLightDotsClass {
  private:
    long lastStarColorUpdate;
    bool lastEnabled;
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

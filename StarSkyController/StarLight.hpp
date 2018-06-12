#pragma once

#include "config.h"
#include "StarStorage.hpp"
#include <NeoPixelBus.h>
#include <vector>

class StarLightMode {
  protected:
    uint32_t timeout;
  public:
    StarLightMode(uint32_t timeout);
    uint32_t getTimeout();
    virtual void setup() {};
    virtual void loop() {};
    virtual RgbwColor color(uint16_t index) { return RgbwColor(0); };
};

class StarLightDotsClass {
  private:
    long lastStarColorUpdate;
    bool lastEnabled;
    std::vector<StarLightMode *> modeList;
    NeoPixelBus<LIGHT_DOTS_COLOR, LIGHT_DOTS_METHOD> strip;
  public:
    StarLightDotsClass();
    void setup();
    void loop();
    void addMode(StarLightMode *mode);
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
    StarLightDotsClass &getDots();
};

extern StarLightClass StarLight;

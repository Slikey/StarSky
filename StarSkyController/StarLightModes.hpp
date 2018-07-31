#pragma once

#include "StarLight.hpp"

class RainbowMode : public StarLightMode {
  private:
    uint8_t hue;
  public:
    RainbowMode();
    void setup();
    void loop();
    RgbwColor color(uint16_t index);
};

class WhiteSparkleMode : public StarLightMode {
  private:
    uint8_t brightness[LIGHT_DOTS_NUM_LEDS];
    uint8_t count;
  public:
    WhiteSparkleMode();
    void setup();
    void loop();
    RgbwColor color(uint16_t index);
};

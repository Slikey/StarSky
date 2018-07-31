#include "StarLightModes.hpp"

//
// RainbowMode
//

RainbowMode::RainbowMode() : StarLightMode(50) {
  hue = 0;
}

void RainbowMode::setup() {}

void RainbowMode::loop() {
  ++hue;
}

RgbwColor RainbowMode::color(uint16_t index) {
  const float part = (float) index / (LIGHT_DOTS_NUM_LEDS - 1);
  const float offset = (float) hue / 0xFF;
  return HsbColor(part + offset, 1.0f, 1.0f);
}

// 
// WhiteSparkleMode
//

WhiteSparkleMode::WhiteSparkleMode()  : StarLightMode(50) {
}

void WhiteSparkleMode::setup() {
  for (uint16_t i = 0; i < LIGHT_DOTS_NUM_LEDS; ++i) {
    if (LedArray.get(i) == 0) {
      brightness[i] = 0; //(uint8_t) random(0xF); 
    } else {
      brightness[i] = 0xF;
    }
  }
}

void WhiteSparkleMode::loop() {
  for (uint16_t i = 0; i < LIGHT_DOTS_NUM_LEDS; ++i) {
    if (LedArray.get(i) == 0) {
      brightness[i] = 0; //(uint8_t) random(0xF); 
    } else {
      brightness[i] = 0xFF;
    }
  }
}

RgbwColor WhiteSparkleMode::color(uint16_t index) {
  return RgbwColor(0, 0, 0, brightness[index]);
}

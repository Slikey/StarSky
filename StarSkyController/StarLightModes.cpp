#include "StarLightModes.hpp"

//
// RainbowMode
//

RainbowMode::RainbowMode() : StarLightMode(10) {
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

WhiteSparkleMode::WhiteSparkleMode()  : StarLightMode(10) {

}

void WhiteSparkleMode::setup() {
  for (uint16_t i = 0; i < LIGHT_DOTS_NUM_LEDS; ++i)
    brightness[i] = (uint8_t) random(0xFF);
}

void WhiteSparkleMode::loop() {
  for (uint16_t i = 0; i < LIGHT_DOTS_NUM_LEDS; ++i)
    brightness[i] += (uint8_t) random(0xF);
}

RgbwColor WhiteSparkleMode::color(uint16_t index) {
  return RgbwColor(0, 0, 0, brightness[index]);
}

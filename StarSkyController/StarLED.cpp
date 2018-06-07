#include "StarLED.hpp"

void StarLEDClass::setup() {
  settings = SPISettings(12000000, MSBFIRST, SPI_MODE0);
  SPI.begin();
}

uint8_t hue = 0;
void StarLEDClass::loop() {
  startBlock();

  for (uint8_t i = 0; i < LIGHT_DOTS_NUM_LEDS; ++i) {
    CRGB rgb = CHSV(hue + i, 255, 255);
    uint32_t val = 0xEE000000 | (rgb.r << 16) | (rgb.g << 8) | rgb.b;
    SPI.transfer32(val);
  }

  ++hue;

  endBlock();
}

void StarLEDClass::startBlock() {
  SPI.beginTransaction(settings);
  SPI.transfer32(0x00000000);
}

void StarLEDClass::endBlock() {
  SPI.transfer32(0xFFFFFFFF);
  SPI.endTransaction();
}

StarLEDClass StarLED;


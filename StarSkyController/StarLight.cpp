#include "StarLight.hpp"

void StarLightClass::setup() {
  lastModCount = -1; // will always run the loop after boot
  lastStarColorUpdate = millis();

  FastLED.addLeds<WS2812B, LIGHT_DOTS_DATA_PIN, RGB>(ledsRGB, getRGBWsize(LIGHT_DOTS_NUM_LEDS));
  FastLED.show();
}

void StarLightClass::loop() {
  int modCount = StarStorage.getModCount();
  if (modCount != lastModCount) {
    lastModCount = modCount;

    Serial.println("[Light] =========== MODE ===========");
    if (!StarStorage.isEnabled()) {
      FastLED.setBrightness(0);
      Serial.println("[Light] StarSky disabled!");
    } else {
      FastLED.setBrightness(LIGHT_DOTS_BRIGHTNESS);
      int brightness = StarStorage.getBrightness();
      if (brightness >= 95) {
        Serial.println("[Light] Main Light ON!");
      }
      float backlight = (float) brightness / 90;
      if (backlight > 1.0) backlight = 1.0;
      if (backlight > 0.0) {
        Serial.printf("[Light] Backlight: %f!\n", backlight * 100.0);
      }

      long msec = millis();
      long timeout = lastStarColorUpdate + 5;
      if (timeout < lastStarColorUpdate || timeout < msec) {
        starColor();
        FastLED.show();
      }
    }
    Serial.println("[Light] =========== STOP ===========");
  }
}

void StarLightClass::starColor() {
  static uint16_t hue;
  static uint8_t w;

  for (int i = 0; i < LIGHT_DOTS_NUM_LEDS; i++) {
    uint8_t hue = (i * 256 / LIGHT_DOTS_NUM_LEDS + hue / 10) & 0xFF;
    leds[i] = CHSV(hue, 255, 255);
    leds[i].w = (w + i * 2) < 128 ? 0 : (w + i * 2) * 2;
  }
  hue++;
  w++;
}

StarLightClass StarLight;

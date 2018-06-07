#include "StarLight.hpp"

void StarLightDotsClass::setup() {
  Serial.printf("[Light-Dots] Pin: %d\n", LIGHT_DOTS_DATA_PIN);
  lastStarColorUpdate = millis();
  FastLED.addLeds<WS2812B, LIGHT_DOTS_DATA_PIN, RGB>(ledsRGB, getRGBWsize(LIGHT_DOTS_NUM_LEDS));
}

void StarLightDotsClass::loop() {
  int brightness = 0;
  if (StarStorage.isEnabled()) {
    long msec = millis();
    long timeout = lastStarColorUpdate + 5;
    if (timeout < lastStarColorUpdate || timeout < msec) {
      starColor();
    }
    brightness = LIGHT_DOTS_BRIGHTNESS;
  }
  FastLED.setBrightness(brightness);
  FastLED.show();
}

void StarLightDotsClass::starColor() {
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

void StarLightBacklightClass::setup() {
  Serial.printf("[Light-Backlight] Pin: %d\n", LIGHT_BACKLIGHT_PIN);
  ledcSetup(LIGHT_BACKLIGHT_CHANNEL, 5000, 8);
  ledcAttachPin(LIGHT_BACKLIGHT_PIN, LIGHT_BACKLIGHT_CHANNEL);
}

void StarLightBacklightClass::loop() {
  int pinVal = 0;
  if (StarStorage.isEnabled()) {
    int brightness = StarStorage.getBrightness();
    if (brightness > 100) brightness = 100;
    if (brightness < 0) brightness = 0;
    float val = (float) brightness / 100.0;
    pinVal = (int) (val * 255);
  }
  ledcWrite(LIGHT_BACKLIGHT_CHANNEL, pinVal);
  Serial.printf("[Light-Backlight] Set backlight level to %d.\n", pinVal);
}

void StarLightMainClass::setup() {
  Serial.printf("[Light-Main] Pin: %d\n", LIGHT_MAIN_PIN);
  pinMode(LIGHT_MAIN_PIN, OUTPUT);
}

void StarLightMainClass::loop() {
  // Pin 5 is inverted :(
  int pinVal = HIGH;
  if (StarStorage.isEnabled() && StarStorage.getBrightness() > 100) {
    pinVal = LOW;
  }
  digitalWrite(LIGHT_MAIN_PIN, pinVal);
  Serial.printf("[Light-Main] Value: %s\n", pinVal == HIGH ? "HIGH" : "LOW");
}

void StarLightClass::setup() {
  lastModCount = -1; // will always run the loop after boot
  dots.setup();
  backlight.setup();
  main.setup();
}

void StarLightClass::loop() {
  int modCount = StarStorage.getModCount();
  if (modCount != lastModCount) {
    lastModCount = modCount;

    dots.loop();
    backlight.loop();
    main.loop();
  }
}

StarLightClass StarLight;

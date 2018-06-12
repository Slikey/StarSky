#include "StarLight.hpp"

NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> strip(LIGHT_DOTS_NUM_LEDS, LIGHT_DOTS_DATA_PIN);
    
void StarLightDotsClass::setup() {
  Serial.printf("[Light-Dots] Pin: %d\n", LIGHT_DOTS_DATA_PIN);
  lastStarColorUpdate = millis();
  lastEnabled = StarStorage.isEnabled();
  strip.Begin();
  strip.Show();
}

void StarLightDotsClass::loop() {
  uint8_t brightness;
  if (StarStorage.isEnabled()) {
    long msec = millis();
    long timeout = lastStarColorUpdate + 10;
    if (timeout <= lastStarColorUpdate || timeout < msec) {
      starColor();
      lastStarColorUpdate = msec;
    }
    strip.Show();
  } else if (lastEnabled) {
    for (int i = 0; i < LIGHT_DOTS_NUM_LEDS; i++) {
      strip.SetPixelColor(i, 0);
    }
    strip.Show();
  }
  lastEnabled = StarStorage.isEnabled();
}

void StarLightDotsClass::starColor() {
  static uint8_t hue;
  static const float led_step = 1.0f / LIGHT_DOTS_NUM_LEDS;
  float offset = (float) hue / 255;
  for (uint16_t i = 0; i < LIGHT_DOTS_NUM_LEDS; i++) {
    float h = led_step * i + offset;
    HsbColor rgb = HsbColor(h, 1.0f, 1.0f);
    RgbwColor rgbw(rgb);
    strip.SetPixelColor(i, rgbw);
  }
  ++hue;
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
  dots.loop();

  int modCount = StarStorage.getModCount();
  if (modCount != lastModCount) {
    lastModCount = modCount;

    backlight.loop();
    main.loop();
  }
}

StarLightClass StarLight;

#include "StarLight.hpp"

StarLightMode::StarLightMode(uint32_t timeout) {
  this->timeout = timeout;
}

uint32_t StarLightMode::getTimeout() {
  return timeout;
}

StarLightDotsClass::StarLightDotsClass() : strip(LIGHT_DOTS_NUM_LEDS, LIGHT_DOTS_DATA_PIN) {}

void StarLightDotsClass::setup() {
  Serial.printf("[Light-Dots] Pin: %d\n", LIGHT_DOTS_DATA_PIN);
  lastStarColorUpdate = millis();
  lastEnabled = StarStorage.isEnabled();
  for (auto it = modeList.begin(); it != modeList.end(); ++it) {
    (*it)->setup();
  }
  strip.Begin();
}

void StarLightDotsClass::loop() {
  if (StarStorage.isEnabled()) {
    const uint32_t msec = millis();
    uint8_t modeIdx = StarStorage.getStarMode();
    if (modeIdx >= modeList.size()) {
      StarStorage.setStarMode(modeIdx = 0);
    }
    StarLightMode *starLightMode = modeList[modeIdx];
    const uint32_t timeout = lastStarColorUpdate + starLightMode->getTimeout();
    if (timeout <= lastStarColorUpdate || timeout < msec) {
      starLightMode->loop();
      for (uint16_t i = 0; i < LIGHT_DOTS_NUM_LEDS; ++i)
        strip.SetPixelColor(i, starLightMode->color(i));
      lastStarColorUpdate = msec;
    }
    strip.Show();
  } else if (lastEnabled) {
    for (uint16_t i = 0; i < LIGHT_DOTS_NUM_LEDS; ++i)
      strip.SetPixelColor(i, 0);
    strip.Show();
  }
  lastEnabled = StarStorage.isEnabled();
}

void StarLightDotsClass::addMode(StarLightMode *starMode) {
  modeList.push_back(starMode);
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
  LedArray.setup();
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

StarLightDotsClass &StarLightClass::getDots() {
  return dots;
}

StarLightClass StarLight;

// LED ARRAY

void LedArrayClass::setup() {
  for (uint16_t i = 0; i < LIGHT_DOTS_NUM_LEDS; ++i) {
    ids[i] = LED_ARRAY_STARS;
  }
  for (uint16_t i = 3; i <= 6; ++i) {
    ids[i] = LED_ARRAY_HELLO_KITTY;
  }
  ids[19] = ids[20] = ids[21] = ids[23] = ids[25] = ids[26] = ids[27] = ids[28] = LED_ARRAY_PONY;
  ids[56] = ids[57] = ids[59] = ids[63] = ids[65] = ids[66] = ids[68] = ids[69] = ids[70] = ids[71] = ids[74] = ids[75] = ids[76] = ids[77] = ids[78] = LED_ARRAY_SUNFLOWER;
  ids[85] = ids[86] = ids[87] = ids[89] = ids[96] = ids[98] = ids[101] = ids[108] = ids[109] = ids[110] = LED_ARRAY_PIKA;
  ids[125] = LED_ARRAY_HEART;
}

uint8_t LedArrayClass::get(uint16_t led) {
  return ids[led];
}

LedArrayClass LedArray;

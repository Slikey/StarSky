#include "StarLight.hpp"

void StarLightClass::setup() {
  lastModCount = StarStorage.getModCount();
}

void StarLightClass::loop() {
  int modCount = StarStorage.getModCount();
  if (modCount == lastModCount) return;
  lastModCount = modCount;

  Serial.println("[Light] =========== MODE ===========");
  if (!StarStorage.isEnabled()) {
    Serial.println("[Light] StarSky disabled!");
  } else {
    int brightness = StarStorage.getBrightness();
    if (brightness >= 95) {
      Serial.println("[Light] Main Light ON!");
    }
    float backlight = (float) brightness / 90;
    if (backlight > 1.0) backlight = 1.0;
    if (backlight > 0.0) {
      Serial.printf("[Light] Backlight: %f!\n", backlight * 100.0);
    }
  }
  Serial.println("[Light] =========== STOP ===========");
}

StarLightClass StarLight;

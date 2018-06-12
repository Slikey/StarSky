#include "StarStorage.hpp"

void StarStorageClass::setup() {
  this->initialised = false;

  Serial.print("[Storage] Loading EEPROM...");
  if (!EEPROM.begin(STORAGE_EEPROM_SIZE)) {
    Serial.println();
    Serial.println("[Storage] Failed to initialise EEPROM");
    return;
  }
  Serial.println(" done!");

  EEPROM.readBytes(0, &data, sizeof(StarStorageData_t));
  Serial.println("[Storage] Reading from EEPROM:");
  Serial.printf("[Storage] Brightness: %d\n", data.brightness);
  Serial.printf("[Storage] Enabled: %s\n", data.enabled ? "true" : "false");
  Serial.printf("[Storage] StarMode: %d\n", data.starMode);

  initialised = true;
  lastUpdate = millis();
  comitted = true;
}

void StarStorageClass::dirty() {
  lastUpdate = millis();
  comitted = false;
}

void StarStorageClass::loop() {
  if (!initialised) return;
  if (comitted) return;
  long timeout = this->lastUpdate + STORAGE_DELAY;
  // check if timeout overflows OR timeout elapsed
  if (lastUpdate > timeout || timeout > millis()) return;

  // when storing values we make them
  if (data.brightness > 100) {
    data.brightness = 110;
    data.modCount++;
  }
  if (data.brightness <= 0) {
    data.brightness = -10;
    data.modCount++;
  }

  EEPROM.writeBytes(0, &data, sizeof(StarStorageData_t));
  EEPROM.commit();
  Serial.printf("[Storage] Written %d.\n", data.brightness);
  comitted = true;
}

int StarStorageClass::getBrightness() {
  return data.brightness;
}

void StarStorageClass::incBrightness(int value) {
  setBrightness(getBrightness() + value);
}

void StarStorageClass::setBrightness(int brightness) {
  int old = data.brightness;
  if (brightness > 110) brightness = 110;
  else if (brightness < -10) brightness = -10;
  if (brightness == old) return;
  data.brightness = brightness;
  data.modCount++;
  dirty();
  Serial.printf("[StarStorage] Brightness changed from %d to %d\n", old, brightness);
}

bool StarStorageClass::isEnabled() {
  return data.enabled;
}

void StarStorageClass::setEnabled(bool enabled) {
  if (enabled == data.enabled) return;
  data.enabled = enabled;
  dirty();
  data.modCount++;
  Serial.printf("[Request] Toggled light to %s\n", enabled ? "true" : "false");
}

uint8_t StarStorageClass::getStarMode() {
  return data.starMode;
}

void StarStorageClass::setStarMode(uint8_t starMode) {
  data.starMode = starMode;
  dirty();
  data.modCount++;
  Serial.printf("[Request] Set StarMode to %d\n", starMode);
}

void StarStorageClass::incStarMode() {
  setStarMode(getStarMode() + 1);
}

uint32_t StarStorageClass::getModCount() {
  return data.modCount;
}

StarStorageClass StarStorage;

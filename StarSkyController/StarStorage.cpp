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

  EEPROM.readBytes(0, &this->data, sizeof(StarStorageData_t));
  Serial.println("[Storage] Reading from EEPROM:");
  Serial.printf("[Storage] Brightness: %d\n", this->data.brightness);
  Serial.printf("[Storage] Enabled: %s\n", this->data.enabled ? "true" : "false");

  this->initialised = true;
  this->lastUpdate = millis();
  this->comitted = true;
}

void StarStorageClass::dirty() {
  this->lastUpdate = millis();
  this->comitted = false;
}

void StarStorageClass::loop() {
  if (!this->initialised) return;
  if (this->comitted) return;
  long timeout = this->lastUpdate + STORAGE_DELAY;
  // check if timeout overflows OR timeout elapsed
  if (this->lastUpdate > timeout || timeout > millis()) return;

  // when storing values we make them
  if (this->data.brightness > 100) {
    this->data.brightness = 110;
    this->data.modCount++;
  }
  if (this->data.brightness <= 0) {
    this->data.brightness = -10;
    this->data.modCount++;
  }

  EEPROM.writeBytes(0, &this->data, sizeof(StarStorageData_t));
  EEPROM.commit();
  Serial.printf("[Storage] Written %d.\n", this->data.brightness);
  this->comitted = true;
}

int StarStorageClass::getBrightness() {
  return this->data.brightness;
}

void StarStorageClass::incBrightness(int value) {
  setBrightness(getBrightness() + value);
}

void StarStorageClass::setBrightness(int brightness) {
  int old = this->data.brightness;
  if (brightness > 110) brightness = 110;
  else if (brightness < -10) brightness = -10;
  if (brightness == old) return;
  this->data.brightness = brightness;
  this->data.modCount++;
  this->dirty();
  Serial.printf("[StarStorage] Brightness changed from %d to %d\n", old, brightness);
}

bool StarStorageClass::isEnabled() {
  return this->data.enabled;
}

void StarStorageClass::setEnabled(bool enabled) {
  if (enabled == this->data.enabled) return;
  this->data.enabled = enabled;
  this->dirty();
  this->data.modCount++;
  Serial.printf("[Request] Toggled light to %s\n", enabled ? "true" : "false");
}

int StarStorageClass::getModCount() {
  return this->data.modCount;
}

StarStorageClass StarStorage;

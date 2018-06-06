#include "StarStorage.hpp"
#include "StarWiFi.hpp"
#include "StarAPI.hpp"
#include "StarLight.hpp"

void setup() {
  Serial.begin(2000000);
  Serial.println("[INFO] Booting!");
  StarStorage.setup();
  StarWiFi.setup();
  StarAPI.setup();
  StarLight.setup();
  Serial.println("[INFO] Booted!");
}

void loop() {
  StarAPI.loop();
  StarStorage.loop();
  StarLight.loop();
}


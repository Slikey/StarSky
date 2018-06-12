#include "StarStorage.hpp"
#include "StarWiFi.hpp"
#include "StarAPI.hpp"
#include "StarLight.hpp"
#include "StarLightModes.hpp"

void setRandomSeed() {
  uint32_t seed = analogRead(0);
  for (int i = 0; i < 4; ++i) {
    seed = (seed << 16) ^ analogRead(i);
  }
  randomSeed(seed);
  Serial.printf("[INFO] Random Seed: %d\n", seed); 
}

void setup() {
  Serial.begin(2000000);
  Serial.println("[INFO] Booting!");
  setRandomSeed();
  
  StarLight.getDots().addMode(new RainbowMode());
  StarLight.getDots().addMode(new WhiteSparkleMode());
  
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


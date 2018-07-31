#include "StarWiFi.hpp"
#include "StarRotary.hpp"
#include "StarButton.hpp"
#include "StarAPI.hpp"

long lastUpdate;

void setup() {
  Serial.begin(2000000);
  StarRotary.setup();
  StarButton.setup();
  StarWiFi.setup();
  lastUpdate = millis();
}

void loop() {
  StarRotary.loop();
  StarButton.loop();
  
  long msec = millis();
  long timeout = lastUpdate + 5;
  // check if timeout overflows OR timeout reached
  if (timeout < lastUpdate || timeout < msec) {
    int ticks = StarRotary.getAndResetTicks();
    if (ticks != 0) {
      StarAPI.requestIncBrightness(ticks);
    }
    if (StarRotary.getAndResetButton()) {
      StarAPI.requestToggle();
    }
    if (StarButton.getAndResetLeftButton()) {
      StarAPI.requestButton(0);
    }
    if (StarButton.getAndResetRightButton()) {
      StarAPI.requestButton(1);
    }
    lastUpdate = msec;
  }
}


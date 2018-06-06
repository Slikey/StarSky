#include "StarWiFi.hpp"
#include "StarRotary.hpp"
#include "StarAPI.hpp"

long lastUpdate;

void setup() {
  Serial.begin(2000000);
  StarRotary.setup();
  StarWiFi.setup();
  lastUpdate = millis();
}

void loop() {
  StarRotary.loop();
  
  long msec = millis();
  long timeout = lastUpdate + 5;
  // check if timeout overflows OR timeout reached
  if (timeout < lastUpdate || timeout < msec) {
    int ticks = StarRotary.getAndResetTicks();
    if (ticks != 0) {
      StarAPI.requestIncBrightness(counter);
    }
    if (StarRotary.getAndResetButton()) {
      StarAPI.requestToggle();
    }
    lastUpdate = msec;
  }
}


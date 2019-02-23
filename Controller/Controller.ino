#include "config.h"
#include "api.h"
#include "store.h"
#include "light.h"

uint32_t next_report = 0;

void random_seed() {
  uint32_t seed = analogRead(0);
  for (int i = 0; i < 4; ++i) {
    seed = (seed << 16) ^ analogRead(i);
  }
  randomSeed(seed);
  Sprintf("[INFO] Random Seed: %d\n", seed);
}

void setup() {
  Sbegin(SERIAL_BAUD);
  Sprintln("[INFO] Booting!");

  random_seed();

  storage_setup();
  api_setup();
  light_setup();
}

void loop() {
  const uint32_t msec = millis();
  storage_loop(msec);
  api_loop(msec);
  light_loop(msec);

#ifdef SERIAL_ENABLED
  if (next_report <= msec) {
    uint32_t seconds = msec / 1000;
    uint32_t minutes = seconds / 60;
    uint32_t hours = minutes / 60;
    seconds %= 60;
    minutes %= 60;
    Sprintf("[INFO] Uptime: %02d:%02d:%02d\n", hours, minutes, seconds);
    next_report += 10000;
  }
#endif

  delay(1);
}



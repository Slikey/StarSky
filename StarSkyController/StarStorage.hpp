#pragma once

#include "config.h"
#include <WiFi.h>
#include <EEPROM.h>

typedef struct {
  int brightness;
  bool enabled;
  uint32_t modCount;
  uint8_t starMode;
} StarStorageData_t;

class StarStorageClass {
  private:
    bool initialised;
    int lastUpdate;
    bool comitted;
    StarStorageData_t data;
    void dirty();
  public:
    StarStorageClass() = default;
    void setup();
    void loop();
    int getBrightness();
    void incBrightness(int value);
    void setBrightness(int brightness);
    bool isEnabled();
    void setEnabled(bool enabled);
    uint8_t getStarMode();
    void setStarMode(uint8_t mode);
    void incStarMode();
    uint32_t getModCount();
};

extern StarStorageClass StarStorage;


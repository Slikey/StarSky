#pragma once

#include "config.h"
#include <WiFi.h>
#include <EEPROM.h>

typedef struct {
  int brightness;
  bool enabled;
  int modCount;
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
    int getModCount();
};

extern StarStorageClass StarStorage;


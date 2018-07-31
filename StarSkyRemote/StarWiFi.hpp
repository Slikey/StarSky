#pragma once

#include "config.h"

class StarWiFiClass {
  public:
    void setup();
    void awaitConnection();
};

extern StarWiFiClass StarWiFi;

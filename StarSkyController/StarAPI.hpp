#pragma once

#include "config.h"
#include "StarStorage.hpp"
#include <WiFi.h>
#include <WiFiUdp.h>

class StarAPIClass {
  private:
    WiFiUDP udp;
    char packet[512];

    void handleRequest();
    void handleBrightness();
    void handleToggle();
  public:
    void setup();
    void loop();
};

extern StarAPIClass StarAPI;

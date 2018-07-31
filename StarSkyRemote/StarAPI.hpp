#pragma once

#include "config.h"
#include "StarWiFi.hpp"
#include <WiFiUdp.h>

class StarAPIClass {
  private:
    WiFiUDP udp;
    char request[512];
    void sendRequest();
  public:
    void requestIncBrightness(int val);
    void requestToggle();
    void requestMode();
    void requestButton(int val);
};

extern StarAPIClass StarAPI;

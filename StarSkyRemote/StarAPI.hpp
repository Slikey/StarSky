#ifndef STAR_API_HEADER
#define STAR_API_HEADER

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
};

extern StarAPIClass StarAPI;

#endif

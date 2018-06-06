#ifndef STAR_WIFI_HEADER
#define STAR_WIFI_HEADER

#include "config.h"

class StarWiFiClass {
  public:
    void setup();
    void awaitConnection();
};

extern StarWiFiClass StarWiFi;

#endif

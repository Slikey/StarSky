#ifndef STAR_LIGHT_HEADER
#define STAR_LIGHT_HEADER

#include "config.h"
#include "StarStorage.hpp"

class StarLightClass {
  private:
    int lastModCount;
  public:
    void setup();
    void loop();
};

extern StarLightClass StarLight;

#endif

#pragma once

#include "config.h"

struct starsky_packet_t {
    uint8_t brightness_change;
    uint8_t toggle_enabled:1;
    uint8_t enable_nightmode:1;
    uint8_t inc_starmode:1;
};

bool packet_has_value(starsky_packet_t *packet) {
    if (packet->brightness_change != 0) return true;
    if (packet->toggle_enabled) return true;
    if (packet->enable_nightmode) return true;
    if (packet->inc_starmode) return true;
    return false;
}
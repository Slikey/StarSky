#include "config.h"
#include "api.h"
#include "button.h"
#include "rotary.h"

void setup() {
  Sbegin(SERIAL_BAUD);
  Sprintln("[INFO] Booting...");

  api_setup();
  button_setup();
  rotary_setup();
}

void loop() {
  uint32_t msec = millis();
  api_loop(msec);
  button_loop(msec);
  rotary_loop(msec);

  starsky_packet_t packet;
  if (button_consume_left()) {
    packet.enable_nightmode = true;
  }
  if (button_consume_right()) {
    packet.inc_starmode = true;
  }
  if (button_consume_rotary()) {
    packet.toggle_enabled = true;
  }
  int8_t rotary_value = rotary_consume();
  packet.brightness_change = rotary_value;
  api_send_packet(&packet);
  delay(5);
}

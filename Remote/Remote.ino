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

  button_consume_left();
  button_consume_right();
  button_consume_rotary();
  rotary_consume();
}

void loop() {
  uint32_t msec = millis();
  button_loop(msec);
  rotary_loop(msec);

  starsky_packet_t packet;
  if (button_consume_left()) {
    packet.enable_nightmode = true;
    Sprintln("Nightmode: toggle");
  }
  if (button_consume_right()) {
    packet.inc_starmode = true;
    Sprintln("Starmode toggle");
  }
  if (button_consume_rotary()) {
    packet.toggle_enabled = true;
    Sprintln("Rotary toggled");
  }
  int8_t rotary_value = rotary_consume();
  packet.brightness_change = rotary_value;
  if (packet.brightness_change != 0) {
    Sprintf("Value: %d\n", packet.brightness_change);
  }
  api_send_packet(&packet);
  delay(5);
}

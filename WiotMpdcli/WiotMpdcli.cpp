#include "wiring_digital.h"
#include "wifi.h"
#include "variant.h"
#include <Arduino.h>

#include "config.h"
#include "mpdcli.h"
#include "buttons.h"
#include "tftfunctions.h"
#include "battery.h"
#include "debug.h"
#include "mpd_commands.h"

extern void test_mpdcli();

void setup() {
  // init debug code
  init_debug();
  // initialize buttons
  init_buttons();
  // Initialize TFT
  init_tft();
  // initialize battery
  init_battery();
  // show mpd_status at startup
  show_mpd_status();
}

void loop() {
  if (digitalRead(WIO_KEY_A) == LOW) {
    show_mpd_status();
  }
  if (digitalRead(WIO_KEY_B) == LOW) {
    printBatteryStats();
  }
  // put your main code here, to run repeatedly:
}

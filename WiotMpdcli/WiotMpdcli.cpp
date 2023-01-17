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
#include "menu.h"

extern void test_mpdcli();

static unsigned long wifi_started = 0;

void setup() {
  // init debug code
  init_debug();
  // initialize buttons
  init_buttons();
  // Initialize TFT
  init_tft();
  // initialize battery
  init_battery();
  if (start_wifi()) {
    wifi_started = millis();
  }
  tft_clear();
  digitalWrite(LCD_BACKLIGHT, LOW);
}

void loop() {
  if (digitalRead(WIO_KEY_A) == LOW) {
    start_wifi();
    wifi_started = millis();
    show_mpd_status();
    wifi_started = millis();
  }
  if (digitalRead(WIO_KEY_B) == LOW) {
    printBatteryStats();
  }
  if (digitalRead(WIO_KEY_C) == LOW) {
    start_wifi();
    toggle_mpd_status();
    wifi_started = millis();
  }
  if (digitalRead(WIO_5S_PRESS) == LOW) {
    start_wifi();
    show_menu();
    wifi_started = millis();
  }
  if ((is_wifi_connected() && (millis() - wifi_started) > 10000UL)) {
    stop_wifi();
  }
}


#include "config.h"

#include "wifi.h"
// #include "variant.h"

#include "battery.h"
#include "buttons.h"
#include "debug.h"
#include "menu.h"
#include "mpd_commands.h"
#include "mpdcli.h"
#include "tftfunctions.h"

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
  // check for SD card with configuration
  if (load_SD_config()) {
    if (save_FLASH_config()) {
      tft_println("Config saved to FLASH");
    }
  } else {
    if (!load_FLASH_config()) {
      tft_println("NO FLASH CONFIG!");
      while (true) {}
    }
  }
  // start wifi
  if (start_wifi(get_config())) {
    tft_clear();
    show_mpd_status();
    wifi_started = millis();
  } else {
    tft_println("Connection FAIL!");
    delay(1000);
  }
  tft_clear();
  digitalWrite(LCD_BACKLIGHT, LOW);
}

void loop() {
  unsigned long wifi_timer = 5000UL;
  if (digitalRead(WIO_KEY_A) == LOW) {
    start_wifi(get_config());
    wifi_started = millis();
    show_mpd_status();
    wifi_started = millis();
  }
  if (digitalRead(WIO_KEY_B) == LOW) {
    printBatteryStats();
  }
  if (digitalRead(WIO_KEY_C) == LOW) {
    start_wifi(get_config());
    toggle_mpd_status();
    wifi_started = millis();
  }
  if (digitalRead(WIO_5S_PRESS) == LOW) {
    start_wifi(get_config());
    show_menu();
    wifi_started = millis();
  }
  if ((is_wifi_connected() && (millis() - wifi_started) > wifi_timer)) {
    stop_wifi();
  }
  delay(1);
}

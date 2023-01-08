#include "wiring_digital.h"
#include "wifi.h"
#include "variant.h"
#include <Arduino.h>

//#include "variant.h"

#include "config.h"
#include "mpdcli.h"
#include "buttons.h"
#include "tftfunctions.h"
#include "battery.h"
#include "debug.h"

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
}

void loop() {
  if (digitalRead(WIO_KEY_A) == LOW) {
    tft_clear();
    digitalWrite(LCD_BACKLIGHT, HIGH);
    tft_println("Connecting...");
    if (start_wifi()) {
      tft_println("connected");
    } else {
      tft_println("can't connect");
    }
    MpdConnection con;
    if (con.Connect(MPD_HOST, MPD_PORT)) {
      con.Disconnect();
    }
    delay(5000);
    digitalWrite(LCD_BACKLIGHT, LOW);
    stop_wifi();
    digitalWrite(LED_BUILTIN, LOW);
  }

  if (digitalRead(WIO_KEY_B) == LOW) {
    digitalWrite(LCD_BACKLIGHT, HIGH);
    printBatteryStats();
    while (digitalRead(WIO_KEY_B) == LOW) {}
    tft_clear();
  } else {
    digitalWrite(LCD_BACKLIGHT, LOW);
  }
  // put your main code here, to run repeatedly:
}

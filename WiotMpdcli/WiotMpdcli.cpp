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
    do {
      yield();
    } while (digitalRead(WIO_KEY_A) == LOW);
    tft_println("KEY_A");
  }

  if (digitalRead(WIO_KEY_B) == LOW) {
    do {
      yield();
    } while (digitalRead(WIO_KEY_A) == LOW);
    printBatteryStats();
  }

  // put your main code here, to run repeatedly:
}

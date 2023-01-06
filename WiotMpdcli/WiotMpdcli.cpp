#include <Arduino.h>

//#include "variant.h"

#include "config.h"
#include "mpdcli.h"
#include "buttons.h"
#include "tftfunctions.h"
#include "debug.h"

extern void test_mpdcli();

void setup() {
  // init debug code
  init_debug();
  // initialize buttons
  init_buttons();
  // Initialize TFT
  init_tft();
}

void loop() {
  if (digitalRead(WIO_KEY_A) == LOW) {
    tft_println("KEY_A");
    do {
      yield();
    } while (digitalRead(WIO_KEY_A) == LOW);
  }

  // put your main code here, to run repeatedly:
}

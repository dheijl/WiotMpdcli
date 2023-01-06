#pragma once

#include "config.h"

void init_debug() {
#ifdef DEBUG
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }
  delay(100);
#ifdef DEBUGMPDMESSAGES
  test_mpdcli();
#endif
#endif
}
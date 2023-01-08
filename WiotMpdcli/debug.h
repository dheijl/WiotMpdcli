#pragma once

#include "config.h"
#include "testmpdcli.h"

void init_debug() {
#ifdef DEBUG
  Serial.begin(115200);
  int n = 250;
  while (!Serial && n-- > 0) {
    delay(1);
  }
  delay(100);
#ifdef DEBUGMPDMESSAGES
  test_mpdcli();
#endif
#endif
}
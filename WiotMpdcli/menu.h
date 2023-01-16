#pragma once

#include <Arduino.h>
#include <Seeed_Arduino_FS.h>
#include <Seeed_SFUD.h>
#include <stdint.h>

#include <vector>
#include <string>

#include "config.h"
#include "flash_fs.h"

using namespace std;

typedef struct menuline {
  uint16_t x;
  uint16_t y;
  const char* text;
} MENULINE;


void show_menu();
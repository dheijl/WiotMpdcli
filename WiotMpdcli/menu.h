#pragma once

#include <Arduino.h>
#include <Seeed_Arduino_FS.h>
#include <Seeed_SFUD.h>
#include <stdint.h>

#include <vector>
#include <string>

#include "config.h"
using namespace std;

typedef struct MENULINE {
  uint16_t x;
  uint16_t y;
  String text;
} menuline;


void show_menu();
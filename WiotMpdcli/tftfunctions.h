#pragma once

#include <string>
#include "TFT_eSPI.h"
#include "Free_Fonts.h"  //include the header file

using namespace std;

void init_tft();
void tft_write(int16_t x, int16_t y, uint16_t color, String s);
void tft_println(const String s);

void tft_clear();
#pragma once

#include <string>
#include "TFT_eSPI.h"
#include "Free_Fonts.h"  //include the header file

void init_tft();
void tft_write(int x, int y, String s);
void tft_println(String s);

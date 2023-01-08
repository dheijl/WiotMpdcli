#pragma once

#include <string>
#include "TFT_eSPI.h"
#include "Free_Fonts.h"  //include the header file

using namespace std;

void init_tft();
void tft_write(int x, int y, string s);
void tft_println(const String s);

void tft_clear();
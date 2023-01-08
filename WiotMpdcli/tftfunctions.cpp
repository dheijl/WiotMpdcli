#include<string>

#include "tftfunctions.h"

TFT_eSPI tft = TFT_eSPI();

void init_tft() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.setFreeFont(FM9);
  tft.println();
  tft.println("TFT initialized!");
}

void tft_write(int x, int y, string s) {
}

void tft_println(const String s) {
  tft.println(s);
}

void tft_clear() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.println();
}
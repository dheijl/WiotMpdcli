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

void tft_write(int16_t x, int16_t y, uint16_t color, const String s) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.print(s.c_str());
  DPRINT(String(x) + ", " + String(y) + ", " + String(color) + ", " + s);
}

void tft_write_error(int16_t x, int16_t y, const String s) {
  tft_write(x, y, TFT_RED, s);
}

void tft_write_highlight(int16_t x, int16_t y, const String s) {
  tft_write(x, y, TFT_GREENYELLOW, s);
}

void tft_println(const String s, uint16_t color) {
  tft.setTextColor(color);
  tft.println(s);
  DPRINT(s);
}

void tft_println_error(const String s) {
  tft_println(s, TFT_RED);
}

void tft_println_highlight(const String s) {
  tft_println(s, TFT_GREENYELLOW);
}

void tft_print(const String s) {
  tft.print(s);
}

void tft_clear() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.println();
}

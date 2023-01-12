#include "menu.h"
#include "tftfunctions.h"


static vector<menuline> main_menu = vector<menuline>({
  { 4, 40, "Select Favourite" },
  { 4, 80, "Select Player" },
  { 4, 120, "Return" },
});

static void display_menuline(menuline line, uint16_t color) {
  tft_write(line.x, line.y, color, line.text);
}

static int display_menu(const vector<menuline> menu) {
  tft_clear();
  int selected = 0;
  bool repaint = true;
  while (true) {
    if (repaint) {
      repaint = false;
      int i = 0;
      for (auto l : menu) {
        if (i++ == selected) {
          display_menuline(l, TFT_GREENYELLOW);
        } else {
          display_menuline(l, TFT_WHITE);
        }
      }
    }
    int down_time = 400;
    if (digitalRead(WIO_5S_UP) == LOW) {
      while ((digitalRead(WIO_5S_UP) == LOW) && (down_time-- > 0)) {
        delay(1);
      }
      selected -= 1;
      if (selected < 0) {
        selected = menu.size() - 1;
      }
      repaint = true;
      continue;
    }
    if (digitalRead(WIO_5S_DOWN) == LOW) {
      while ((digitalRead(WIO_5S_DOWN) == LOW) && (down_time-- > 0)) {
        delay(1);
      }
      selected += 1;
      if (selected > (menu.size() - 1)) {
        selected = 0;
      }
      repaint = true;
      continue;
    }
    if (digitalRead(WIO_5S_RIGHT) == LOW) {
      return selected;
    }
    if (digitalRead(WIO_5S_LEFT) == LOW) {
      return -1;
    }
    delay(1);
  }
}

void show_menu() {
  tft_clear();
  digitalWrite(LCD_BACKLIGHT, HIGH);
  int selected = display_menu(main_menu);
  /*
  digitalWrite(LCD_BACKLIGHT, HIGH);
  write_ip("192.168.0.129");
  vector<char> current_ip; 
  read_ip(current_ip);
  string ip(current_ip.begin(), current_ip.end());
  tft_println("IP=" + String(ip.c_str()));
 */
  delay(500);
  digitalWrite(LCD_BACKLIGHT, LOW);
  tft_clear();
}
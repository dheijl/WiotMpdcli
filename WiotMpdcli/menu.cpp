#include "flash_fs.h"
#include "menu.h"
#include "tftfunctions.h"


static vector<menuline> main_menu = vector<menuline>({
  { 4, 40, "Select Favourite" },
  { 4, 80, "Select Player" },
  { 4, 120, "Return" },
});

static vector<menuline> player_menu = vector<menuline>({
  { 4, 40, PLAYER1_NAME },
  { 4, 80, PLAYER2_NAME },
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
      while ((digitalRead(WIO_5S_RIGHT) == LOW) && (down_time-- > 0)) {
        delay(1);
      }
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
  switch (selected) {
    case -1:  // return
      break;
    case 0:  // select favourite
      break;
    case 1:  // select player
      selected = display_menu(player_menu);
      break;
    default:  // impossible, ignore
      break;
  }
  delay(500);
  digitalWrite(LCD_BACKLIGHT, LOW);
  tft_clear();
}
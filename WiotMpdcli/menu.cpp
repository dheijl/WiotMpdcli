#include "flash_fs.h"
#include "menu.h"
#include "tftfunctions.h"


static vector<MENULINE*> main_menu = vector<MENULINE*>({
  new MENULINE { 4, 40, "Select Favourite" },
  new MENULINE { 4, 80, "Select Player" },
  new MENULINE { 4, 120, "Return" },
});

static void display_menuline(const MENULINE* line, uint16_t color) {
  tft_write(line->x, line->y, color, String(line->text));
}

static int display_menu(const vector<MENULINE*> menu) {
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
      {
        auto players = get_player_info();
        vector<MENULINE*> player_menu;
        uint16_t pos = 40;
        for (auto p : *players) {
          MENULINE* m = new MENULINE { 4, pos, p.player_name };
          DPRINT("Name: " + String(m->text));
          pos += 40;
          player_menu.push_back(m);
        }
        MENULINE *ret = new MENULINE { 4, pos, "Return" };
        player_menu.push_back(ret);
        for (auto l: player_menu) {
          DPRINT("Name: " + String(l->text));
        }
        selected = display_menu(player_menu);

        //
        player_menu.clear();
      }
      break;
    default:  // impossible, ignore
      break;
  }
  delay(500);
  digitalWrite(LCD_BACKLIGHT, LOW);
  tft_clear();
}
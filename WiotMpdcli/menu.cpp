#include "mpd_commands.h"
#include "flash_fs.h"
#include "menu.h"
#include "tftfunctions.h"


static vector<MENULINE*> main_menu = vector<MENULINE*>({
  new MENULINE{ 4, 40, "Select Favourite" },
  new MENULINE{ 4, 80, "Select Player" },
  new MENULINE{ 4, 120, "Return" },
});

static vector<FAVOURITE*> favourites = vector<FAVOURITE*>({
  new FAVOURITE{ "Radio Delfino", "https://nr8.newradio.it/proxy/emaamo00?mp=/stream" },
  new FAVOURITE{ "Radio 1 Classics", "http://icecast.vrtcdn.be/radio1_classics_high.mp3" },
  new FAVOURITE{ "Radio 1", "http://icecast.vrtcdn.be/radio1-high.mp3" },
  new FAVOURITE{ "Radio 2 OVL", "http://icecast.vrtcdn.be/ra2ovl-high.mp3" },
  new FAVOURITE{ "Classics 21", "https://radios.rtbf.be/classic21-128.mp3" },
  new FAVOURITE{ "D.I. Blues", "http://orion.shoutca.st:8990/stream" },
  new FAVOURITE{ "D.I. Jazz", "http://orion.shoutca.st:8950/stream" },
  new FAVOURITE{ "R. Paradise Rock", "http://stream.radioparadise.com/rock-flacm" },
  new FAVOURITE{ "StuBru Tijdloze", "http://icecast.vrtcdn.be/stubru_tijdloze-high.mp3" },
  new FAVOURITE{ "Willy", "https://playerservices.streamtheworld.com/api/livestream-redirect/WILLY.mp3" },
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

static void select_player() {
  auto players = get_player_info();
  vector<MENULINE*> player_menu;
  uint16_t pos = 40;
  for (auto p : players) {
    MENULINE* m = new MENULINE{ 4, pos, p.player_name };
    DPRINT("Name: " + String(m->text));
    pos += 40;
    player_menu.push_back(m);
  }
  MENULINE* ret = new MENULINE{ 4, pos, "Return" };
  player_menu.push_back(ret);
  int selected = display_menu(player_menu);
  if ((selected >= 0) && (selected < player_menu.size())) {
    auto ip = players[selected].player_ip;
    tft_clear();
    tft_println("New player @" + String(ip));
    write_player_ip(ip);
  }
  for (auto ml = player_menu.begin(); ml != player_menu.end(); ++ml) {
    delete *ml;
  }
  player_menu.clear();
  delay(500);
}

static void select_favourite() {
  vector<MENULINE*> fav_menu;
  uint16_t pos = 15;
  for (auto f : favourites) {
    MENULINE* m = new MENULINE{ 4, pos, f->fav_name };
    pos += 20;
    fav_menu.push_back(m);
  }
  MENULINE* ret = new MENULINE{ 4, pos, "Return" };
  fav_menu.push_back(ret);
  int selected = display_menu(fav_menu);
  if ((selected >= 0) && (selected < fav_menu.size())) {
    auto url = favourites[selected]->fav_url;
    auto name = favourites[selected]->fav_name;
    tft_clear();
    tft_println("Play " + String(name));
    play_favourite(url);
  }
  for (auto ml = fav_menu.begin(); ml != fav_menu.end(); ++ml) {
    delete *ml;
  }
  fav_menu.clear();
}

void show_menu() {
  tft_clear();
  digitalWrite(LCD_BACKLIGHT, HIGH);
  int selected = display_menu(main_menu);
  switch (selected) {
    case -1:  // return
      break;
    case 0:  // select favourite
      select_favourite();
      break;
    case 1:  // select player
      select_player();
      break;
    default:  // impossible, ignore
      break;
  }
  delay(500);
  digitalWrite(LCD_BACKLIGHT, LOW);
  tft_clear();
}
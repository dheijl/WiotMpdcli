#include "menu.h"
#include "tftfunctions.h"

static void write_ip(const char* new_ip) {
  while (!SFUD.begin(104000000UL)) {
    DPRINT("FLASH Mount Failed");
    tft_println("FLASH mount failed");
    return;
  }
  tft_println("FLASH mounted");
  File ipfile = SFUD.open("ip.txt", FILE_WRITE);
  if (ipfile) {
    ipfile.println(new_ip);
    ipfile.close();
    tft_println("Saved " + String(new_ip));
  } else {
    DPRINT("Can't write file");
    tft_println("Can't write file");
  }
}

static void read_ip(vector<char>& current_ip) {
  File ipfile = SFUD.open("ip.txt", FILE_READ);
  if (ipfile) {
    String ip = "";
    if (ipfile.available()) {
      ip = ipfile.readStringUntil('\n');
    }
    DPRINT("Read ip:" + ip);
    tft_println("Read ip:" + ip);
    ipfile.close();
    current_ip.clear();
    for (auto c : ip) {
      current_ip.push_back(c);
    }
  } else {
    DPRINT("Can't read file");
    tft_println("Can't read file");
  }
}

static vector<menuline> main_menu = vector<menuline>({
  { 4, 40, "Select Player" },
  { 4, 80, "Select Favourite" },
  { 4, 120, "exit" },
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
    if (digitalRead(WIO_5S_UP) == LOW) {
      while (digitalRead(WIO_5S_UP) == LOW) {
        delay(1);
      }
      selected -= 1;
      if (selected < 0) {
        selected = 0;
      }
      repaint = true;
      continue;
    }
    if (digitalRead(WIO_5S_DOWN) == LOW) {
      while (digitalRead(WIO_5S_DOWN) == LOW) {
        delay(1);
      }
      selected += 1;
      if (selected > (menu.size() - 1)) {
        selected = menu.size() - 1;
      }
      repaint = true;
      continue;
    }
    if (digitalRead(WIO_5S_PRESS) == LOW) {
      while (digitalRead(WIO_5S_PRESS) == LOW) {
        delay(1);
      }
      return selected;
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

#include "sdcard_fs.h"

vector<string*> players;

vector<string*> favourites;

bool read_players() {

  if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI, 4000000UL)) {
    tft_println("No Config SD Card");
    SD.end();
    return false;
  }

  File plf = SD.open("players.txt", FILE_READ);
  if (plf) {
    tft_println("Init players..");
    while (plf.available()) {
      String pl = plf.readStringUntil('\n');
      if (pl.length() > 1) {
        tft_println(pl);
        players.push_back(new string(pl.c_str()));
      }
    }
    plf.close();
    SD.end();
    return true;
  } else {
    SD.end();
    return false;
  }
  return false;
}

bool read_favourites() {

  if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI, 4000000UL)) {
    SD.end();
    return false;
  }

  File favf = SD.open("favs.txt", FILE_READ);
  if (favf) {
    tft_println("Init favourites..");
    while (favf.available()) {
      String fav = favf.readStringUntil('\n');
      if (fav.length() > 1) {
        favourites.push_back(new string(fav.c_str()));
      }
    }
    favf.close();
    SD.end();
    tft_println("Loaded " + String(favourites.size()) + " favourites");
    return true;
  } else {
    SD.end();
    return false;
  }
  return false;
}

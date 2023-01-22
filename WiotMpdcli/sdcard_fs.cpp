#include "tftfunctions.h"
#include "config.h"

#include "sdcard_fs.h"

vector<MPD_PLAYER *> mpd_players;

vector<FAVOURITE *> favourites;

static vector<string> split(const string &s, char delim) {
  vector<string> result;
  size_t start;
  size_t end = 0;

  while ((start = s.find_first_not_of(delim, end)) != std::string::npos) {
    end = s.find(delim, start);
    result.push_back(s.substr(start, end - start));
  }
  return result;
}

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
      string pl = plf.readStringUntil('\n').c_str();
      if (pl.length() > 1) {
        vector<string> parts = split(pl, '|');
        if (parts.size() == 3) {
          MPD_PLAYER *mpd = new MPD_PLAYER();
          mpd->player_ip = strdup(parts[0].c_str());
          mpd->player_name = strdup(parts[1].c_str());
          mpd->player_port = stoi(parts[2]);
          mpd_players.push_back(mpd);
          tft_println(String(mpd->player_ip) + " " + String(mpd->player_name) + " " + String(mpd->player_port));
        }
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
      string fav = favf.readStringUntil('\n').c_str();
      if (fav.length() > 1) {
        vector<string> parts = split(fav, '|');
        if (parts.size() == 2) {
          FAVOURITE *f = new FAVOURITE();
          f->fav_name = strdup(parts[0].c_str());
          f->fav_url = strdup(parts[1].c_str());
          favourites.push_back(f);
        }
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

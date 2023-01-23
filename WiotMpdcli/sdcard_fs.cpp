#include "tftfunctions.h"
#include "config.h"

#include "sdcard_fs.h"

static CONFIG config;

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

CONFIG &get_config() {
  return config;
}

bool read_wifi() {

  if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI, 4000000UL)) {
    SD.end();
    return false;
  }
  File wifif = SD.open("wifi.txt", FILE_READ);
  if (wifif) {
    tft_println("Loading WiFi ssid/psw");
    while (wifif.available()) {
      string wifi = wifif.readStringUntil('\n').c_str();
      if (wifi.length() > 1) {
        vector<string> parts = split(wifi, '|');
        if (parts.size() == 2) {
          auto l = parts[0].length();
          if ((parts[0].at(0) == '"') && (parts[0].at(l - 1) == '"')) {
            string ssid = parts[0];
            ssid.erase(0, 1);
            ssid.erase(l - 2, 1);
            config.ssid = strdup(ssid.c_str());
          }
          l = parts[1].length();
          if ((parts[1].at(0) == '"') && (parts[1].at(l - 1) == '"')) {
            string psw = parts[1];
            psw.erase(0, 1);
            psw.erase(l - 2, 1);
            config.psw = strdup(psw.c_str());
          }
        }
      }
    }
    wifif.close();
    SD.end();
    return true;
  } else {
    SD.end();
    return false;
  }
  return false;
}

bool read_players() {

  if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI, 4000000UL)) {
    tft_println("No Config SD Card");
    SD.end();
    return false;
  }

  File plf = SD.open("players.txt", FILE_READ);
  if (plf) {
    tft_println("Loading players");
    while (plf.available()) {
      string pl = plf.readStringUntil('\n').c_str();
      if (pl.length() > 1) {
        vector<string> parts = split(pl, '|');
        if (parts.size() == 3) {
          MPD_PLAYER *mpd = new MPD_PLAYER();
          mpd->player_ip = strdup(parts[0].c_str());
          mpd->player_name = strdup(parts[1].c_str());
          mpd->player_port = stoi(parts[2]);
          config.mpd_players.push_back(mpd);
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
    tft_println("Loading favourites");
    while (favf.available()) {
      string fav = favf.readStringUntil('\n').c_str();
      if (fav.length() > 1) {
        vector<string> parts = split(fav, '|');
        if (parts.size() == 2) {
          FAVOURITE *f = new FAVOURITE();
          f->fav_name = strdup(parts[0].c_str());
          f->fav_url = strdup(parts[1].c_str());
          config.favourites.push_back(f);
        }
      }
    }
    favf.close();
    SD.end();
    tft_println("Loaded " + String(config.favourites.size()) + " favourites");
    return true;
  } else {
    SD.end();
    return false;
  }
  return false;
}

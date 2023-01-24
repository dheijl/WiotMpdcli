#include "tftfunctions.h"
#include "config.h"

#include "sdcard_fs.h"

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

bool read_wifi_SD(CONFIG &config) {
  bool result = false;
  if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI, 4000000UL)) {
    SD.end();
    return result;
  }
  tft_println("SD card present!");
  File wifif = SD.open("wifi.txt", FILE_READ);
  if (wifif) {
    tft_println("Loading WiFi ssid/psw");
    while (wifif.available()) {
      string wifi = wifif.readStringUntil('\n').c_str();
      if (wifi.length() > 1) {
        vector<string> parts = split(wifi, '|');
        if (parts.size() == 2) {
          config.ssid = strdup(parts[0].c_str());
          config.psw = strdup(parts[1].c_str());
          result = true;
        }
      }
    }
    wifif.close();
  }
  SD.end();
  return result;
}

bool read_players_SD(CONFIG &config) {
  bool result = false;
  if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI, 4000000UL)) {
    SD.end();
    return result;
  }
  File plf = SD.open("players.txt", FILE_READ);
  if (plf) {
    tft_println("Loading players:");
    while (plf.available()) {
      string pl = plf.readStringUntil('\n').c_str();
      if (pl.length() > 1) {
        vector<string> parts = split(pl, '|');
        if (parts.size() == 3) {
          MPD_PLAYER *mpd = new MPD_PLAYER();
          mpd->player_name = strdup(parts[0].c_str());
          mpd->player_ip = strdup(parts[1].c_str());
          mpd->player_port = stoi(parts[2]);
          config.mpd_players.push_back(mpd);
          tft_println(String(mpd->player_name) + " " + String(mpd->player_ip) + ":" + String(mpd->player_port));
        }
      }
    }
    plf.close();
    if (config.mpd_players.size() > 0) {
      result = true;
    } else {
      tft_println("No players!");
    }
  }
  SD.end();
  return result;
}

bool read_favourites_SD(CONFIG &config) {
  bool result = false;
  if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI, 4000000UL)) {
    SD.end();
    return result;
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
    if (config.favourites.size() > 0) {
      tft_println("Loaded " + String(config.favourites.size()) + " favourites");
      result = true;
    } else {
      tft_println("No favourites!");
    }
  }
  SD.end();
  return result;
}

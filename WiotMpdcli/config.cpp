#include "config.h"

#include "sdcard_fs.h"
#include "flash_fs.h"


static CONFIG config;

static vector<string> split(const string& s, char delim) {
  vector<string> result;
  size_t start;
  size_t end = 0;

  while ((start = s.find_first_not_of(delim, end)) != std::string::npos) {
    end = s.find(delim, start);
    result.push_back(s.substr(start, end - start));
  }
  return result;
}


bool load_SD_config() {
  if (read_wifi_SD(config) && read_players_SD(config) && read_favourites_SD(config)) {
    return true;
  } else {
    return false;
  }
}

bool load_FLASH_config() {
  return true;
}

bool save_FLASH_config() {
  return true;
}


CONFIG& get_config() {
  return config;
}

bool parse_wifi_file(File wifif, CONFIG& config) {
  bool result = false;
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
  return result;
}

bool parse_players_file(File plf, CONFIG& config) {
  bool result = false;
  tft_println("Loading players:");
  while (plf.available()) {
    string pl = plf.readStringUntil('\n').c_str();
    if (pl.length() > 1) {
      vector<string> parts = split(pl, '|');
      if (parts.size() == 3) {
        MPD_PLAYER* mpd = new MPD_PLAYER();
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
  return result;
}

bool parse_favs_file(File favf, CONFIG& config) {
  bool result = false;
  tft_println("Loading favourites");
  while (favf.available()) {
    string fav = favf.readStringUntil('\n').c_str();
    if (fav.length() > 1) {
      vector<string> parts = split(fav, '|');
      if (parts.size() == 2) {
        FAVOURITE* f = new FAVOURITE();
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
  return result;
}
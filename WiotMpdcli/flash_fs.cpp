#include <string>
#include <cstdlib>
#include "config.h"
#include "flash_fs.h"
#include "tftfunctions.h"


bool write_wifi_FLASH(CONFIG& config) {
  bool result = false;
  if (!SFUD.begin(104000000UL)) {
    tft_println("FLASH mount failed");
    return result;
  }
  if (SFUD.remove("wifi.txt")) {
    tft_println("wifi.txt removed");
  }
  String data = String(config.ssid) + "|" + String(config.psw);
  File wifif = SFUD.open("wifi.txt", FILE_WRITE);
  if (wifif) {
    wifif.println(data);
    DPRINT(data.c_str());
    wifif.close();
    result = true;
  } else {
    tft_println_error("Error writing wifi.txt");
  }
  SFUD.end();
  return result;
}


bool write_player_FLASH(CONFIG& config) {
  bool result = false;
  if (!SFUD.begin(104000000UL)) {
    tft_println_error("FLASH mount failed");
    return result;
  }
  if (SFUD.remove("players.txt")) {
    tft_println("players.txt removed");
  }
  File plf = SFUD.open("players.txt", FILE_WRITE);
  if (plf) {
    for (auto pl : config.mpd_players) {
      String data = String(pl->player_name) + "|" + String(pl->player_ip) + "|" + String(to_string(pl->player_port).c_str());
      plf.println(data);
      DPRINT(data.c_str());
    }
    plf.close();
    result = true;
  } else {
    tft_println_error("Error writing wifi.txt");
  }
  SFUD.end();
  return result;
}

bool write_favourites_FLASH(CONFIG& config) {
  bool result = false;
  if (!SFUD.begin(104000000UL)) {
    tft_println_error("FLASH mount failed");
    return result;
  }
  if (SFUD.remove("favs.txt")) {
    tft_println("favs.txt removed");
  }
  File favf = SFUD.open("favs.txt", FILE_WRITE);
  if (favf) {
    for (auto f : config.favourites) {
      String data = String(f->fav_name) + "|" + String(f->fav_url);
      favf.println(data);
      DPRINT(data.c_str());
    }
    favf.close();
    result = true;
  } else {
    tft_println_error("Error writing favs.txt");
  }
  SFUD.end();
  return result;
}

bool read_wifi_FLASH(CONFIG& config) {
  bool result = false;
  if (!SFUD.begin(104000000UL)) {
    tft_println_error("FLASH mount failed");
    return result;
  }
  File wifif = SFUD.open("wifi.txt", FILE_READ);
  if (wifif) {
    result = parse_wifi_file(wifif, config);
  }
  SFUD.end();
  return result;
}

bool read_players_FLASH(CONFIG& config) {
  bool result = false;
  if (!SFUD.begin(104000000UL)) {
    tft_println_error("FLASH mount failed");
    return result;
  }
  File plf = SFUD.open("players.txt", FILE_READ);
  if (plf) {
    result = parse_players_file(plf, config);
  }
  SFUD.end();
  return result;
}

bool read_favourites_FLASH(CONFIG& config) {
  bool result = false;
  if (!SFUD.begin(104000000UL)) {
    tft_println_error("FLASH mount failed");
    return result;
  }
  File favf = SFUD.open("favs.txt", FILE_READ);
  if (favf) {
    result = parse_favs_file(favf, config);
  }
  SFUD.end();
  return result;
}


void write_current_player(const MPD_PLAYER& new_pl) {
  if (!SFUD.begin(104000000UL)) {
    tft_println_error("FLASH mount failed");
    return;
  }
  tft_println("FLASH mounted");
  File ipfile = SFUD.open("curmpd.txt", FILE_WRITE);
  if (ipfile) {
    ipfile.println(String(new_pl.player_name) + "|" + String(new_pl.player_ip) + "|" + String(to_string(new_pl.player_port).c_str()));
    ipfile.close();
    tft_println("Saved " + String(new_pl.player_name));
  } else {
    tft_println_error("Can't write file");
  }
  SFUD.end();
}

MPD_PLAYER read_current_player() {
  MPD_PLAYER current_player{ NULL, NULL, 0 };
  if (!SFUD.begin(104000000UL)) {
    tft_println_error("FLASH mount failed");
    return current_player;
  }
  File current_mpd = SFUD.open("curmpd.txt", FILE_READ);
  if (current_mpd) {
    String line = "";
    if (current_mpd.available()) {
      line = current_mpd.readStringUntil('\n');
      line.trim();
    }
    current_mpd.close();
    string data = string(line.c_str());
    auto parts = split(data, '|');
    if (parts.size() == 3) {
      current_player.player_name = strdup(parts[0].c_str());
      current_player.player_ip = strdup(parts[1].c_str());
      current_player.player_port = atoi(parts[2].c_str());
      DPRINT(String(current_player.player_name) + " " + String(current_player.player_ip) + " " + String(current_player.player_port));
    }
  }
  if (current_player.player_ip == NULL) {
    tft_println_error("Can't read curmpd.txt");
    auto player = get_config().mpd_players[0];
    current_player.player_name = player->player_name;
    current_player.player_ip = player->player_ip;
    current_player.player_port = player->player_port;
    write_current_player(current_player);
  }
  SFUD.end();
  return current_player;
}

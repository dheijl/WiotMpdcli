#include "flash_fs.h"
#include "tftfunctions.h"

static vector<MPD_PLAYER> players = {
  {
    PLAYER1_NAME,
    PLAYER1_IP,
    PLAYER1_PORT,
  },
  {
    PLAYER2_NAME,
    PLAYER2_IP,
    PLAYER2_PORT,
  },
};

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
    tft_println("Error writing wifi.txt");
  }
  SFUD.end();
  return result;
}


bool write_player_FLASH(CONFIG& config) {
  bool result = false;
  if (!SFUD.begin(104000000UL)) {
    tft_println("FLASH mount failed");
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
    tft_println("Error writing wifi.txt");
  }
  SFUD.end();
  return result;
}

bool write_favourites_FLASH(CONFIG& config) {
  bool result = false;
  if (!SFUD.begin(104000000UL)) {
    tft_println("FLASH mount failed");
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
    tft_println("Error writing favs.txt");
  }
  SFUD.end();
  return result;
}

bool read_wifi_FLASH(CONFIG& config) {
  bool result = false;
  if (!SFUD.begin(104000000UL)) {
    tft_println("FLASH mount failed");
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
    tft_println("FLASH mount failed");
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
    tft_println("FLASH mount failed");
    return result;
  }
  File favf = SFUD.open("favs.txt", FILE_READ);
  if (favf) {
    result = parse_favs_file(favf, config);
  }
  SFUD.end();
  return result;
}


void write_player_ip(const char* new_ip) {
  if (!SFUD.begin(104000000UL)) {
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
    tft_println("Can't write file");
  }
  SFUD.end();
}

void read_player_ip(vector<char>& current_ip) {
  if (!SFUD.begin(104000000UL)) {
    tft_println("FLASH mount failed");
    return;
  }
  File ipfile = SFUD.open("ip.txt", FILE_READ);
  if (ipfile) {
    String ip = "";
    if (ipfile.available()) {
      ip = ipfile.readStringUntil('\n');
    }
    ipfile.close();
    current_ip.clear();
    for (auto c : ip) {
      current_ip.push_back(c);
    }
  } else {
    tft_println("Can't read ip.txt");
    write_player_ip(players[0].player_ip);
    current_ip.clear();
    for (auto c : String(players[0].player_ip)) {
      current_ip.push_back(c);
    }
  }
  SFUD.end();
}

const vector<MPD_PLAYER>& get_player_info() {
  return players;
}

vector<MPD_PLAYER>& get_players() {
  return players;
}

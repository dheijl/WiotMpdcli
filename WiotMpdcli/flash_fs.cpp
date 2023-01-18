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

vector<MPD_PLAYER>& get_players() {
  return players;
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

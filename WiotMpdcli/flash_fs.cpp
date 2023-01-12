#include "flash_fs.h"
#include "tftfunctions.h"

static char* MPD_IPS[] = {
 "192.168.0.129",
 "192.168.0.254",
};


static void write_ip(const char* new_ip) {
  while (!SFUD.begin(104000000UL)) {
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
  while (!SFUD.begin(104000000UL)) {
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
    write_ip(MPD_IPS[0]);
    current_ip.clear();
    for (auto c : String(MPD_IPS[0])) {
      current_ip.push_back(c);
    }
  }
  SFUD.end();
}

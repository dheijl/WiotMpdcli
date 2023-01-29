#include "tftfunctions.h"
#include "config.h"

#include "sdcard_fs.h"

bool read_wifi_SD(CONFIG &config) {
  bool result = false;
  if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI, 4000000UL)) {
    SD.end();
    return result;
  }
  tft_println("SD card present!");
  File wifif = SD.open("wifi.txt", FILE_READ);
  if (wifif) {
    result = parse_wifi_file(wifif, config);
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
    result = parse_players_file(plf, config);
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
    result = parse_favs_file(favf, config);
  }
  SD.end();
  return result;
}

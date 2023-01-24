#include "config.h"

#include "sdcard_fs.h"

static CONFIG config;

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


CONFIG &get_config() {
  return config;
}

#include "config.h"

#include "sdcard_fs.h"

bool load_config() {
  if (read_wifi() && read_players() && read_favourites()) {
    return true;
  } else {
    return false;
  }
}
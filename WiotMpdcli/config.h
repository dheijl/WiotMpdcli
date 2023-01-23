#pragma once

#include <Arduino.h>
#include <vector>

using namespace std;

#undef DEBUG
//#define DEBUG
#undef DEBUGMPDMESSAGES

#ifdef DEBUG
#define DPRINT(x) Serial.println(x);
#else
#define DPRINT(x)
#endif

typedef struct mpd_player {
  const char *player_name;
  const char *player_ip;
  uint16_t player_port;
} MPD_PLAYER;

typedef struct favourite {
  const char *fav_name;
  const char *fav_url;
} FAVOURITE;

typedef struct config {
  const char *ssid;
  const char *psw;
  vector<MPD_PLAYER *> mpd_players;
  vector<FAVOURITE *> favourites;
} CONFIG;

bool load_config();
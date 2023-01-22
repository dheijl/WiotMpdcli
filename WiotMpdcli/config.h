#pragma once

#include <Arduino.h>

#undef DEBUG
//#define DEBUG 
#undef DEBUGMPDMESSAGES 

#ifdef DEBUG
#define DPRINT(x) Serial.println(x);
#else
#define DPRINT(x)
#endif

typedef struct mpd_player {
  const char* player_name;
  const char* player_ip;
  uint16_t player_port;
} MPD_PLAYER;

typedef struct favourite {
  const char *fav_name;
  const char *fav_url;
} FAVOURITE;


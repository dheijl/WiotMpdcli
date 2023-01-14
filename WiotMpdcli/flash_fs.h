#pragma once

#include <Arduino.h>
#include <Seeed_Arduino_FS.h>
#include <Seeed_SFUD.h>

#include <vector>
#include <string>

#include "config.h"

using namespace std;


#define PLAYER1_NAME "Beneden"
#define PLAYER1_IP "192.168.0.129"
#define PLAYER1_PORT "6600"

#define PLAYER2_NAME "Boven"
#define PLAYER2_IP "192.168.0.254"
#define PLAYER2_PORT "6600"

typedef struct mpd_player {
  string player_name;
  string player_ip;
  string player_port;
} MPD_PLAYER;


void read_player_ip(vector<char>&);

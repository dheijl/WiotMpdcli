#pragma once

#include <Arduino.h>
#include <vector>
#include <string>

#include "config.h"

using namespace std;


#define PLAYER1_NAME "Beneden"
#define PLAYER1_IP "192.168.0.129"
#define PLAYER1_PORT 6600

#define PLAYER2_NAME "Boven"
#define PLAYER2_IP "192.168.0.254"
#define PLAYER2_PORT 6600


void read_player_ip(vector<char>&);
void write_player_ip(const char* ip);

const vector<MPD_PLAYER>& get_player_info();

bool write_wifi_FLASH(CONFIG& config);
bool write_player_FLASH(CONFIG& config);
bool write_favourites_FLASH(CONFIG& config);

bool read_wifi_FLASH(CONFIG& config);
bool read_players_FLASH(CONFIG& config);
bool read_favourites_FLASH(CONFIG& config);

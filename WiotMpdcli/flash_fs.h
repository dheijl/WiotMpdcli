#pragma once

#include "config.h"

MPD_PLAYER read_current_player();
void write_current_player(const MPD_PLAYER& new_pl);

bool write_wifi_FLASH(CONFIG& config);
bool write_player_FLASH(CONFIG& config);
bool write_favourites_FLASH(CONFIG& config);

bool read_wifi_FLASH(CONFIG& config);
bool read_players_FLASH(CONFIG& config);
bool read_favourites_FLASH(CONFIG& config);

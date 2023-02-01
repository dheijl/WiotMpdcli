#pragma once

#include "config.h"
#include "flash_fs.h"
#include "mpdcli.h"
#include "tftfunctions.h"

void show_mpd_status();
void toggle_mpd_status();
void play_favourite(const char* url);

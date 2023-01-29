#pragma once

#include <Arduino.h>
#include <string>

using namespace std;

#include "config.h"
#include "mpdcli.h"
#include "flash_fs.h"
#include "tftfunctions.h"

void show_mpd_status();
void toggle_mpd_status();
void play_favourite(const char *url);

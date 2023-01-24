#include <Arduino.h>

#include <vector>

#include <Seeed_Arduino_FS.h>

#include "config.h"
#include "tftfunctions.h"

using namespace std;

bool read_wifi_SD(CONFIG &config);
bool read_players_SD(CONFIG &config);
bool read_favourites_SD(CONFIG &config);

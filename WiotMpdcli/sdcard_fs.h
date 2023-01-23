#include <Arduino.h>

#include <vector>

#include <Seeed_Arduino_FS.h>

#include "config.h"
#include "tftfunctions.h"

using namespace std;

bool read_wifi();
bool read_players();
bool read_favourites();
CONFIG& get_config();

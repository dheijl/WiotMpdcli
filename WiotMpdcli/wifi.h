#pragma once

#include "config.h"
#include <rpcWiFi.h>

bool is_wifi_connected();
bool start_wifi(CONFIG& config);
void stop_wifi();

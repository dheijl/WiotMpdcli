#pragma once

#include <rpcWiFi.h>

#include "config.h"
#include "secret.h"

bool is_wifi_connected();
bool start_wifi();
void stop_wifi();
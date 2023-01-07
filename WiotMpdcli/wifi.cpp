#include "config.h"



#include "wifi.h"


bool start_wifi() {

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  DPRINT("Connecting to WiFi..");
  WiFi.begin(WIFI_SSID, WIFI_PSW);
  if (WiFi.status() == WL_CONNECTED) {
    return true;
  } else {
    return false;
  }
}

void stop_wifi() {
  DPRINT("Disconnect wifi");
  WiFi.disconnect();
  delay(100);
}

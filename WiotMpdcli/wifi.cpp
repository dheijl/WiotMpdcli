#include "config.h"

#include "wifi.h"


bool start_wifi() {

  //Turn on WiFi
  //pinMode(RTL8720D_CHIP_PU, OUTPUT);
  //digitalWrite(RTL8720D_CHIP_PU, HIGH);
  delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.begin(WIFI_SSID, WIFI_PSW);
  if (WiFi.status() == WL_CONNECTED) {
    return true;
  } else {
    return false;
  }
}

void stop_wifi() {
  WiFi.disconnect();
  delay(100);
  //Turn off WiFi
  //pinMode(RTL8720D_CHIP_PU, OUTPUT);
  //digitalWrite(RTL8720D_CHIP_PU, LOW);
}

#include "wifi.h"
#include "tftfunctions.h"

static bool have_wifi = false;

bool is_wifi_connected() {
  return have_wifi;
}

bool start_wifi(CONFIG& config) {

  digitalWrite(LCD_BACKLIGHT, HIGH);
  if ((have_wifi) && (WiFi.status() == WL_CONNECTED)) {
    return true;
  }

  // Turn on WiFi
  // pinMode(RTL8720D_CHIP_PU, OUTPUT);
  // digitalWrite(RTL8720D_CHIP_PU, HIGH);
  // delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  tft_println("Connecting WiFi...");
  WiFi.begin(config.ssid, config.psw);
  if (WiFi.status() == WL_CONNECTED) {
    have_wifi = true;
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    have_wifi = false;
  }
  return have_wifi;
}

void stop_wifi() {
  digitalWrite(LCD_BACKLIGHT, HIGH);
  tft_println("Disconnect Wifi");
  WiFi.disconnect();
  have_wifi = false;
  delay(400);
  tft_clear();
  // Turn off WiFi
  // pinMode(RTL8720D_CHIP_PU, OUTPUT);
  // digitalWrite(RTL8720D_CHIP_PU, LOW);
  digitalWrite(LCD_BACKLIGHT, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}


#include <Arduino.h>

#include "config.h"
#include "mpdcli.h"
#include "tftfunctions.h"
#include "show_mpd_status.h"

void show_mpd_status() {
    tft_clear();
    digitalWrite(LCD_BACKLIGHT, HIGH);
    tft_println("Connecting WiFi...");
    if (start_wifi()) {
      tft_println("Connected.");
    } else {
      tft_println("Can't connect.");
    }
    MpdConnection con;
    if (con.Connect(MPD_HOST, MPD_PORT)) {
      con.GetStatus();
      con.GetCurrentSong();
      con.Disconnect();
    }
    delay(5000);
    while (digitalRead(WIO_KEY_A) == LOW) {
      delay(100);
    }
    digitalWrite(LCD_BACKLIGHT, LOW);
    stop_wifi();
    digitalWrite(LED_BUILTIN, LOW);
}

#include <Arduino.h>

#include "config.h"
#include "mpdcli.h"
#include "tftfunctions.h"
#include "mpd_commands.h"

bool init_wifi() {
  tft_clear();
  digitalWrite(LCD_BACKLIGHT, HIGH);
  tft_println("Connecting WiFi...");
  if (start_wifi()) {
    tft_println("Connected.");
    return true;
  } else {
    tft_println("Can't connect.");
    return false;
  }
}

void exit_wifi() {
  stop_wifi();
  digitalWrite(LCD_BACKLIGHT, LOW);
  tft_clear();
  digitalWrite(LED_BUILTIN, LOW);
}

void toggle_mpd_status() {
  if (init_wifi()) {
    MpdConnection con;
    if (con.Connect(MPD_HOST, MPD_PORT)) {
      if (con.IsPlaying()) {
        tft_println("Stop playing");
        con.Stop();
      } else {
        tft_println("Start playing");
        con.Play();
      }
      con.Disconnect();
    }
    delay(2000);
    while (digitalRead(WIO_KEY_A) == LOW) {
      delay(100);
    }
    exit_wifi();
  }
}

void show_mpd_status() {
  if (init_wifi()) {
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
    exit_wifi();
  }
}
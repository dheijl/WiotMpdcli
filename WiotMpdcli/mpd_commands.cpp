
#include <Arduino.h>

#include "config.h"
#include "mpdcli.h"
#include "tftfunctions.h"
#include "mpd_commands.h"
#include "flash_fs.h"

static string MPD_HOST = "";
static const int MPD_PORT = 6600;

static bool connect_mpd() {
  digitalWrite(LCD_BACKLIGHT, HIGH);
  tft_println("Connecting WiFi...");
  if (start_wifi()) {
    tft_println("Connected.");
    vector<char> ip;
    read_player_ip(ip);
    MPD_HOST = string(ip.begin(), ip.end());
    tft_println(String("Player: " + String(MPD_HOST.c_str())));
    return true;
  } else {
    tft_println("Can't connect.");
    return false;
  }
}

static void disconnect_mpd() {
  stop_wifi();
  digitalWrite(LCD_BACKLIGHT, LOW);
  tft_clear();
  digitalWrite(LED_BUILTIN, LOW);
}

void toggle_mpd_status() {
  if (connect_mpd()) {
    MpdConnection con;
    if (con.Connect(MPD_HOST.c_str(), MPD_PORT)) {
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
    disconnect_mpd();
  }
}

void show_mpd_status() {
  if (connect_mpd()) {
    MpdConnection con;
    if (con.Connect(MPD_HOST.c_str(), MPD_PORT)) {
      con.GetStatus();
      con.GetCurrentSong();
      con.Disconnect();
    }
    delay(5000);
    while (digitalRead(WIO_KEY_A) == LOW) {
      delay(100);
    }
    disconnect_mpd();
  }
}

void play_favourite(const char *url) {
  if (connect_mpd()) {
    MpdConnection con;
    if (con.Connect(MPD_HOST.c_str(), MPD_PORT)) {
      con.Clear();
      con.Add_Url(url);
      con.Play();
    }
    delay(2000);
    disconnect_mpd();
  }
}
#include "mpd_commands.h"

static string MPD_HOST = "";
static const int MPD_PORT = 6600;

static MPD_PLAYER get_mpd() {
  digitalWrite(LCD_BACKLIGHT, HIGH);
  if (start_wifi(get_config())) {
    MPD_PLAYER player = read_current_player();
    tft_println("Player: " + String(player.player_ip));
    return player;
  } else {
    tft_println("Can't connect.");
    return MPD_PLAYER{ NULL, NULL, 0 };
  }
}

static void disconnect_mpd() {
  digitalWrite(LCD_BACKLIGHT, LOW);
  tft_clear();
}

void toggle_mpd_status() {
  auto player = get_mpd();
  if (player.player_ip != NULL) {
    MpdConnection con;
    if (con.Connect(player.player_ip, player.player_port)) {
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
    free((void *)player.player_ip);
    free((void *)player.player_name);
  }
}

void show_mpd_status() {
  auto player = get_mpd();
  if (player.player_ip != NULL) {
    MpdConnection con;
    if (con.Connect(player.player_ip, player.player_port)) {
      con.GetStatus();
      con.GetCurrentSong();
      con.Disconnect();
    }
    delay(3000);
    while (digitalRead(WIO_KEY_A) == LOW) {
      delay(100);
    }
    disconnect_mpd();
    free((void *)player.player_ip);
    free((void *)player.player_name);
  }
}

void play_favourite(const char *url) {
  auto player = get_mpd();
  if (player.player_ip != NULL) {
    MpdConnection con;
    if (con.Connect(player.player_ip, player.player_port)) {
      con.Clear();
      con.Add_Url(url);
      con.Play();
    }
    delay(2000);
    disconnect_mpd();
  }
}
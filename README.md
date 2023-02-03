# WiotMpdcli

Remote Wio Terminal ( + Wio Battery Chassis 650 mAH) MPD client (Arduino IDE)

A basic MPD client that shows the currently playing song on a headless RPI with MoodeAudio (or any other MPD based music player I guess).

Because power saving (standby mode) does not work at this moment on the Wio Terminal, the TFT screen is disabled and you have to push the KEY_A button to activate WiFi, connect to the MPD player, display the current status (play/stop), song, artist and file/radio station for some seconds:

## showing MPD status

![20230108_204345](https://user-images.githubusercontent.com/2384545/211216045-9a59f470-efb1-4133-93de-d24f1fe82a49.jpg)

## showing battery status

![20230108_204513](https://user-images.githubusercontent.com/2384545/211216060-d9735eac-7844-421d-bec2-12d0c01fd79d.jpg)

## Operation

Pushing Key_A will display the current MPD status (play/stop, current file, current artist/song)

Pushing KEY_B will display the battery status while the key is down.

Pushing KEY_C acts as a toggle for starting/stopping the MPD player.

Keep the button pressed to prevent the screen (power) saver to kick in after a few seconds.

The joystick (5S) is used for a menu system that allows you to:

- select a player from a list of players (max 5 players supported)
- select a favourite page from a list of favourites pages (max 50 favourites, so max 5 pages of 10 favourites each). You can then select one of the 10 favourites in that page.

Pushing down the joystick pops up the menu
Pushing right selects
Pushing up/down moves the selection up/down
Pushing left cancels the menu
  
## configuration

The currently active MPD player is stored in the 4MB on board QSPI flash, using Seed's SFUD file system, so that it survives power-off and reset without needing an SD card.

At power-on or reset the SD card slot is checked for the presence of an SD card with configuration files:

- wifi.txt: textfile containing a single line with Wifi SSID and password separated by a | (pipe). No spaces or quotes.
- players.txt: textfile containing up to 5 lines each with a player name and ipv4-address separated by a | (pipe). No spaces or quotes.
- favs.txt: textfile containing up to 50 lines each with a favourite name and an url separated by a | (pipe). No spaces or quotes.

If present these files are read in and copied to internal QSPI flash using the Seeed SFUD file system. At subsequents power-ons this flash config is used (unless an SD card is present with a new config).

After this initialization the WiFi connection is established, and the _status/current file or url/currentsong_ of the active MPD player is shown for a couple of seconds. The wifi connection is kept active for 5 seconds after the last button press (except battery status as it does not need wifi). The blue LED is ON while the WiFi connection is established, and OFF when there is currently no WiFi connection. The WiFi connection will be re-established as needed, and dropped after the 5 second time-out.
The TFT screen is always kept disabled except for some seconds when something is being shown after power-on or a button press, or while a button is kept pressed
down.

The favourites are all internet radio stations in my use case. I haven't tried anything else.

## GUI

The GUI is extremely basic, with this display one could do much better. But I hate GUI design, and it gives me the information I need. Feel free to make pull resuests if GUI is your thing...

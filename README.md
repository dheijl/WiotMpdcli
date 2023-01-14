# WiotMpdcli

Remote Wio Terminal ( + Wio Battery Chassis 650 mAH) MPD client (Arduino IDE)

A basic MPD client that shows the currently playing song on a headless RPI with MoodeAudio (or any other MPD based music player I guess).

Because power saving (standby mode) does not work at this moment on the Wio Terminal, the TFT screen is disabled and you have to push the KEY_A button to activate WiFi, connect to the MPD player, display the current status (play/stop), song, artist and file/radio station for some seconds:

![20230108_204345](https://user-images.githubusercontent.com/2384545/211216045-9a59f470-efb1-4133-93de-d24f1fe82a49.jpg)

Pushing KEY_B will display the battery status while the key is down.

![20230108_204513](https://user-images.githubusercontent.com/2384545/211216060-d9735eac-7844-421d-bec2-12d0c01fd79d.jpg)

KEY_C acts as a toggle for starting/stopping the MPD player.

WIP: the joystick is used for a menu system that allows you to:

- select a player from a list
- select a favourite from a list
- ???
  
The currently active MPD player IP address is stored in the 4MB on board QSPI flash, using Seed's SFUD file system, so that it survives power-off and reset without needing an SD card.

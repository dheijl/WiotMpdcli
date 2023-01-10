#pragma once

#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <algorithm>

#include "wifi.h"
#include "tftfunctions.h"

using namespace std;

static const char* MPD_HOST = "192.168.0.129";
static const int MPD_PORT = 6600;

static const string MPD_CURRENTSONG = "currentsong\n";
static const string MPD_STATUS = "status\n";
static const string MPD_START = "play\n";
static const string MPD_STOP = "stop\n";

enum MpdResponseType {
  MpdOKType,
  MpdACKType,
  MpdErrorType,
};

enum MpdResponseKind {
  MpdUninitializedKind,
  MpdConnectKind,
  MpdCurrentSongKind,
  MpdStatusKind,
  MpdCommandType,
  MpdFailureKind,
};


class MpdResponse {
private:
  MpdResponseType ResponseType;
  string Response;
protected:
  MpdResponseKind ResponseKind;
  std::map<string, string> ResponseData;
  string getItem(const string& item) {
    auto it = this->ResponseData.find(item);
    if (it != this->ResponseData.end()) {
      return it->second;
    } else {
      return "";
    }
  }
  virtual void abstract() = 0;
public:
  MpdResponse(const string response) {
    this->ResponseKind = MpdUninitializedKind;
    this->Response = response;
    auto p = response.find("ACK");
    if (p != string::npos) {
      if (p == 0) {
        this->ResponseType = MpdACKType;
      }
    } else {
      p = response.find("OK");
      if (p != string::npos) {
        if ((p == (response.length() - 3)) || (p == 0)) {
          this->ResponseType = MpdOKType;
        }
      } else {
        this->ResponseType = MpdErrorType;
      }
    }
    // parse response into vector and then into map
    if (this->ResponseType == MpdOKType) {
      // build a vector of the response lines
      string delimiter = "\n";
      size_t pos_start = 0, pos_end, delim_len = delimiter.length();
      string token;
      vector<string> lines;
      while ((pos_end = this->Response.find(delimiter, pos_start)) != string::npos) {
        token = this->Response.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        lines.push_back(token);
      }
      lines.push_back(this->Response.substr(pos_start));
      // now extract key-value pairs into the map
      for (auto line : lines) {
        if ((pos_start = line.find(": ")) != string::npos) {
          auto key = line.substr(0, pos_start);
          std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {
            return std::toupper(c);
          });
          auto value = line.substr(pos_start + 2);
          this->ResponseData[key] = value;
        }
      }
    }
  }
  string getResponseString() {
    return this->Response;
  }
  MpdResponseType getResponseType() {
    return this->ResponseType;
  }
  MpdResponseKind getResponseKind() {
    return this->ResponseKind;
  }
};


class MpdConnect : public MpdResponse {
private:
  string Version;
  void abstract() override {}
public:
  MpdConnect(const string response)
    : MpdResponse(response) {
    this->ResponseKind = MpdConnectKind;
    this->Version = this->getResponseString();
    int p = this->Version.find('\n');
    if (p > 0) {
      this->Version.erase(p, 1);
    }
  }
  string getVersion() {
    return this->Version;
  }
};

class MpdCurrentSong : public MpdResponse {
private:
  void abstract() override {}
public:
  MpdCurrentSong(const string response)
    : MpdResponse(response) {
    if (this->getResponseType() == MpdOKType) {
      this->ResponseKind = MpdCurrentSongKind;
    } else {
      this->ResponseKind = MpdFailureKind;
    }
  }
  string getFile() {
    return this->getItem("FILE");
  }
  string getName() {
    return this->getItem("NAME");
  }
  string getTitle() {
    return this->getItem("TITLE");
  }
};

class MpdStatus : public MpdResponse {
private:
  void abstract() override {}
public:
  MpdStatus(const string response)
    : MpdResponse(response) {
    if (this->getResponseType() == MpdOKType) {
      this->ResponseKind = MpdStatusKind;
    } else {
      this->ResponseKind = MpdFailureKind;
    }
  }
  string getState() {
    return this->getItem("STATE");
  }
};

class MpdSimpleCommand : public MpdResponse {
private:
  void abstract() override {}
public:
  MpdSimpleCommand(const string response)
    : MpdResponse(response) {
    if (this->getResponseType() == MpdOKType) {
      this->ResponseKind = MpdCommandType;
    } else {
      this->ResponseKind = MpdFailureKind;
    }
  }
  string GetResult() {
    return this->getResponseType() == MpdOKType ? "OK" : "ERROR ";
  }
};

class MpdConnection {
private:
  WiFiClient Client;
  string read_data() {
    int n = 5000;
    while (n-- > 0) {
      delay(1);
      if (Client.available()) {
        break;
      }
    }
    if (n <= 0) {
      tft_println("no response");
      return string();
    }
    uint8_t buf[4096];
    int bufsize = sizeof(buf) / sizeof(uint8_t);
    n = Client.read(buf, sizeof(buf));
    string data((char*)&buf[0], n);
    return data;
  }
protected:
public:
  bool Connect(const char* host, int port) {
    DPRINT("Connect to MPD");
    if (Client.connect(host, port)) {
      tft_println("CON MPD @" + String(host) + ":" + String(port));
      string data = read_data();
      if (data.length() == 0) {
        return false;
      }
      DPRINT(data.c_str());
      MpdConnect con(data);
      String v = String(con.getVersion().c_str());
      tft_println(v);
      return true;
    } else {
      DPRINT("MPD Connection failed");
      tft_println("MPD Connection failed");
      return false;
    }
  }
  void Disconnect() {
    DPRINT("Disconnect MPD");
    Client.stop();
  }
  bool GetStatus() {
    DPRINT("Get Status");
    Client.write(MPD_STATUS.c_str(), MPD_STATUS.length());
    string data = read_data();
    if (data.length() == 0) {
      return false;
    }
    DPRINT(data.c_str());
    MpdStatus mpd_status(data);
    tft_println(mpd_status.getState().c_str());
    return true;
  }
  bool GetCurrentSong() {
    DPRINT("GetCurrentSong");
    Client.write(MPD_CURRENTSONG.c_str(), MPD_CURRENTSONG.length());
    string data = read_data();
    if (data.length() == 0) {
      return false;
    }
    DPRINT(data.c_str());
    MpdCurrentSong mpd_cs(data);
    tft_println(mpd_cs.getName().c_str());
    tft_println(mpd_cs.getTitle().c_str());
    String file = String(mpd_cs.getFile().c_str());
    int p = file.lastIndexOf('/');
    file = file.substring(p + 1);
    tft_println(file);
    return true;
  }
  bool Stop() {
    DPRINT("Stop Play");
    Client.write(MPD_STOP.c_str(), MPD_STOP.length());
    string data = read_data();
    if (data.length() == 0) {
      return false;
    }
    DPRINT(data.c_str());
    MpdSimpleCommand mpd_command(data);
    tft_println(mpd_command.GetResult().c_str());
    return true;
  }
  bool Play() {
    DPRINT("Start Play");
    Client.write(MPD_START.c_str(), MPD_START.length());
    string data = read_data();
    if (data.length() == 0) {
      return false;
    }
    DPRINT(data.c_str());
    MpdSimpleCommand mpd_command(data);
    tft_println(mpd_command.GetResult().c_str());
    return true;
  }

};

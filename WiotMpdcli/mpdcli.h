#pragma once

#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

static const string MPD_CURRENTSONG = "currentsong";
static const string MPD_STATUS = "status";

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
		}
		else {
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
		}
		else {
			p = response.find("OK");
			if (p != string::npos) {
				if ((p == (response.length() - 3)) || (p == 0)) {
					this->ResponseType = MpdOKType;
				}
			}
			else {
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
			for (auto line: lines) {
				if ((pos_start = line.find(": ")) != string::npos) {
					auto key = line.substr(0, pos_start);
					std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::toupper(c); });
					auto value = line.substr(pos_start + 2);
					this->ResponseData[key] = value;
				}
			}

		}
	}
	string getResponseString() {
		return this->Response;
	}
	MpdResponseType getResonseType() {
		return this->ResponseType;
	}
	MpdResponseKind getResponseKind() {
		return this->ResponseKind;
	}
};


class MpdConnect: public MpdResponse {
private:
	string Version;
	void abstract() override {}
public:
	MpdConnect(const string response) : MpdResponse(response) {
		this->ResponseKind = MpdConnectKind;
	}
	string getVersion() {
		return this->Version;
	}
};


class MpdCurrentSong: public MpdResponse {
private:
	void abstract() override {}
public:
	MpdCurrentSong(const string response): MpdResponse(response)
	{
		if (this->getResonseType() == MpdOKType) {
			this->ResponseKind = MpdCurrentSongKind;
		}
		else {
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

class MpdStatus: public MpdResponse {
private:
	void abstract() override {}
public:
	MpdStatus(const string response) : MpdResponse(response) {
		if (this->getResonseType() == MpdOKType) {
			this->ResponseKind = MpdStatusKind;
		} else {
			this->ResponseKind = MpdFailureKind;
		}
	}
	string getState() {
		return this->getItem("STATE");
	}
};

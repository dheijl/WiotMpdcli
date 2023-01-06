
#include <Arduino.h>
#include "mpdcli.h"

void test_mpdcli()
{
	// MpdResponse resp("abstract class"); 
	Serial.println("DEBUG MDP MESSAGES");
	MpdConnect con("OK MPD 0.23.5\n");
  Serial.println(con.getResponseString().c_str());
	Serial.printf("ResponseKind=%d\n",con.getResponseKind());
	const string status =
		"volume: 80\n"\
		"repeat: 0\n"\
		"random: 0\n"\
		"single: 0\n"\
		"consume: 0\n"\
		"partition: default\n"\
		"playlist: 1911\n"\
		"playlistlength: 1\n"\
		"mixrampdb: 0\n"\
		"state: stop\n"\
		"song: 0\n"\
		"songid: 16\n"\
		"OK\n";
	MpdStatus st(status);
  Serial.println(st.getResponseString().c_str());
	Serial.printf("ResponseKind=%d\n", st.getResponseKind());
	const string currentsong =
		"file: http://icecast.vrtcdn.be/stubru_tijdloze-high.mp3\n"\
		"Title: De Tijdloze\n"\
		"Name: StuBru De Tijdloze | Kwaliteit * **\n"\
		"Pos: 0\n"\
		"Id: 16\n"\
		"OK\n";
	MpdCurrentSong cs(currentsong);
  Serial.println(cs.getResponseString().c_str());
	Serial.printf("ResponseKind=%d\n", cs.getResponseKind());
	Serial.printf("Current Title: %s\n", cs.getTitle().c_str());
	Serial.printf("Current File: %s\n", cs.getFile().c_str());
	Serial.printf("Current Name: %s\n", cs.getName().c_str());
}

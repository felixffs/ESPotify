//  ESPotify for Heltec Wifi Kit v3 
// -----------------------------------------------
//  This Sketch uses the Heltec Wifi Kit v3 as a small Status display for Spotify to show the song, album, artist and a progress bar
//  for the song that is currently playing. 
//  It uses the spotify API for Arduino and ESP by witnessmenow (https://github.com/witnessmenow/spotify-api-arduino/tree/main), the ArduinoJson library
// by bblanchon (https://github.com/bblanchon/ArduinoJson) and the libraries for the Heltec Wifi Kit v3 board.
// Because of the Sketch being specific to the Heltec board, things might not work as intended if you use the Sketch on another board. 

#include <WiFiClientSecure.h>
#include <SpotifyArduinoCert.h>
#include <SpotifyArduino.h>
#include <ArduinoJson.h>
#include <heltec.h>
#include <Arduino.h>
#include <WiFi.h>

char ssid[] = "";         // your network SSID (name)
char password[] = "";     // your network password

char clientId[] = "";     // Your client ID of your spotify APP
char clientSecret[] = ""; // Your client Secret of your spotify APP (Do Not share this!)

#define SPOTIFY_MARKET "" // Your Spotify Market Region
#define SPOTIFY_REFRESH_TOKEN "" // Can be generated with a Sketch similiar to this one https://github.com/witnessmenow/spotify-api-arduino/blob/main/examples/getRefreshToken/getRefreshToken.ino


WiFiClientSecure client;
SpotifyArduino spotify(client, clientId, clientSecret, SPOTIFY_REFRESH_TOKEN);


// -----------------------------------------------------------------------------------------------------


void printCurrentlyPlayingToScreen(CurrentlyPlaying currentlyPlaying)
{
  if(currentlyPlaying.isPlaying){
    Heltec.display->clear();
    Heltec.display->drawString(0,0,currentlyPlaying.trackName);
    Heltec.display->drawString(0,18,currentlyPlaying.artists[0].artistName);
    Heltec.display->drawString(0,36,currentlyPlaying.albumName);
    long progress = currentlyPlaying.progressMs;
    long duration = currentlyPlaying.durationMs;
    float percentage = ((float)progress / (float)duration) * 100;
    int clampedPercentage = (int)percentage;
    Heltec.display->drawProgressBar(0,54,120,4,clampedPercentage);
    Heltec.display->display();
  }
  else{
    Heltec.display->clear();
    Heltec.display->display();
  }
}

void WIFISetUp(void) // The function connects the ESP to your Wifi with the status displayed at boot
{
	// Set WiFi to station mode and disconnect from an AP if it was previously connected
	delay(1000);
	WiFi.mode(WIFI_STA);
	WiFi.setAutoConnect(true);
	WiFi.begin(ssid, password);
	delay(100);

	byte count = 0;
	while(WiFi.status() != WL_CONNECTED && count < 10)
	{
		count ++;
		delay(500);
		Heltec.display -> drawString(0, 0, "Connecting...");
		Heltec.display -> display();
	}

	Heltec.display -> clear();
	if(WiFi.status() == WL_CONNECTED)
	{
		Heltec.display -> drawString(0, 0, "Connected.");
		Heltec.display -> display();
		//delay(500);
	}
	else
	{
		Heltec.display -> clear();
		Heltec.display -> drawString(0, 0, "Failed to connect.");
		Heltec.display -> display();
		//while(1);
	}
	Heltec.display -> drawString(0, 10, "WiFi Setup done.");
	Heltec.display -> display();
	delay(500);
  Heltec.display -> clear();
  Heltec.display -> display();
}

void setup() 
{
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);

  Heltec.display->init();
  Heltec.display->clear();
  Heltec.display->display();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setContrast(255);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  client.setCACert(spotify_server_cert);
  
  WIFISetUp();

  if(spotify.refreshAccessToken()) //LED blinks for half a second if the connection to Spotify via the Token is functioning properly
  {
    pinMode(LED,OUTPUT);
	  digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
  }
}

void loop() 
{    
  spotify.getCurrentlyPlaying(printCurrentlyPlayingToScreen, SPOTIFY_MARKET);
}

# ESPotify for Heltec Wifi Kit v3

ESPotify is an Arduino Sketch for the Heltec Wifi Kit v3 that Displays the song currently being played on Spotify. It uses the spotify API for Arduino and ESP by witnessmenow (https://github.com/witnessmenow/spotify-api-arduino), the ArduinoJson library by bblanchon (https://github.com/bblanchon/ArduinoJson) and the libraries for the Heltec Wifi Kit v3 board.

## Dependencies

You will need to Install the [Spotify API for Arduino and ESP by witnessmenow](https://github.com/witnessmenow/spotify-api-arduino). Simply download the .zip and Install to the Arduino IDE. 

[ArduinoJson by bblanchon]([https://github.com/bblanchon/ArduinoJson](https://github.com/bblanchon/ArduinoJson)) is needed too. It can be installed via the library manager. 

For the Heltec Wifi Kit v3 board you will also need to install the [libraries for the board by Heltec](https://github.com/HelTecAutomation/Heltec_ESP32). 


## Spotify Token

To use the Sketch, you will need to create a new application on the [Spotify Developer page](https://developer.spotify.com/dashboard/login) and get the client ID and client Secret from there, as well as a callback URL. After that, you will need to generate your refresh token with the getRefreshToken Sketch included in the repository (thanks to witnessmenow for the Script).

## Installation


Finally, you need to set your SSID, Wifi-Password and the previously generated tokens for Spotify in the ESPotify.ino Sketch. 
#
Troubleshooting: 
- the connection status is displayed at boot as part of the Wifi-Setup. 
- if the Connection to Spotify is Working the on-board LED will blink white for 1/2 second. 

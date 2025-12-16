/*
 * Basic Sketch for automatic update of firmware at start
 * with firmware version control
 *
 * Renzo Mischianti <www.mischianti.org>
 *
 * https://mischianti.org
 * https://mischianti.org/esp8266-self-ota-update-firmware-from-server-with-version-check-2/
*/
 
#include <Arduino.h>
 
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
 
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
 
#ifndef APSSID
#define APSSID "Timi_Home"
#define APPSK  "timi397home_"
#endif
 
ESP8266WiFiMulti WiFiMulti;
 
#define FIRMWARE_VERSION "0.3"
 
void update_started() {
  Serial.println("CALLBACK:  HTTP update process started");
}
 
void update_finished() {
  Serial.println("CALLBACK:  HTTP update process finished");
}
 
void update_progress(int cur, int total) {
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}
 
void update_error(int err) {
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}
 
void setup() {
 
  Serial.begin(115200);
//   Serial.setDebugOutput(true);
 
  Serial.println();
  Serial.println();
  Serial.println();
 
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
 
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(APSSID, APPSK);
 
  Serial.print(F("Firmware version "));
  Serial.println(FIRMWARE_VERSION);
  delay(2000);
}
 
 
void loop() {
    // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
 
    WiFiClient client;
 
    // The line below is optional. It can be used to blink the LED on the board during flashing
    // The LED will be on during download of one buffer of data from the network. The LED will
    // be off during writing that buffer to flash
    // On a good connection the LED should flash regularly. On a bad connection the LED will be
    // on much longer than it will be off. Other pins than LED_BUILTIN may be used. The second
    // value is used to put the LED on. If the LED is on with HIGH, that value should be passed
    ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);
 
    // Add optional callback notifiers
    ESPhttpUpdate.onStart(update_started);
    ESPhttpUpdate.onEnd(update_finished);
    ESPhttpUpdate.onProgress(update_progress);
    ESPhttpUpdate.onError(update_error);
 
    ESPhttpUpdate.rebootOnUpdate(false); // remove automatic update
 
    Serial.println(F("Update start now!"));
 
     t_httpUpdate_return ret = ESPhttpUpdate.update(client, "https://upgrade.timi.at/esp8266_ota.ino.d1_mini.bin");
    // Or:
//    t_httpUpdate_return ret = ESPhttpUpdate.update(client, "192.168.1.70", 3000, "/update", FIRMWARE_VERSION);
 
    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        Serial.println(F("Retry in 10secs!"));
        delay(10000); // Wait 10secs
        break;
 
      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        Serial.println("Your code is up to date!");
          delay(10000); // Wait 10secs
        break;
 
      case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        delay(1000); // Wait a second and restart
        ESP.restart();
        break;
    }
  }
}
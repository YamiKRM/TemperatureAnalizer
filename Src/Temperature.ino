#include <ESP8266WiFi.h>
#include <Ubidots.h>

#include "DHTesp.h"

#pragma region DEFINES

#define SSID "CLARO_WIFIA13"
#define PASSWORD "CLAROIAC6"

#define DEVICE_LABEL "esp"
#define DEVICE_NAME "ESP"

#define SECOND 1000
#define DHTPIN 16

#pragma endregion

constexpr char* token = "BBFF-cLSzBm5VcnThK32Zf67FswacdWbqtv";

DHTesp dht;
float temperature = 0;
Ubidots ubidots(token, UBI_HTTP);

void setup() 
{
  
  Serial.begin(9600);
  Serial.print("Setup!");

  if (!ubidots.wifiConnect(SSID, PASSWORD)) 
  {

    Serial.print("Not connected!");

  }

  dht.setup(DHTPIN, DHTesp::DHT22);

}

void loop() 
{
  
  delay(SECOND * 3);
  temperature = dht.getTemperature();

  //Serial.println(temperature);
  ubidots.add("temperature", temperature);

  if (!ubidots.send(DEVICE_LABEL, DEVICE_NAME)) 
  {

    Serial.println("Dind't send.");

  }
  else 
  {

    Serial.println("Sent data.");

  }
}
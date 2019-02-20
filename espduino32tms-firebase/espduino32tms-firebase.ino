
//Required HTTPClientESP32Ex library to be installed  https://github.com/mobizt/HTTPClientESP32Ex

#include "espduino32tms.h"
#include <WiFi.h>
#include "RealTimeStore.h"

RealTimeStore realTimeStore(PATHFB);

float temperature = 0.0;
float humedity = 0.0;

void setup()
{

  Serial.begin(115200);
  connectWIFI();
  realTimeStore.connect(FIREBASE_HOST,FIREBASE_AUTH);

}

void loop()
{
  temperature = tmsTemperatureRead();
  humedity = tmsHumedityRead();
  realTimeStore.sendIntValue(TEMPERATURE, temperature);
  realTimeStore.sendIntValue(HUMEDITY, humedity);
  delay(10000);
}

void connectWIFI()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi...");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("------------------------------");
}

float tmsTemperatureRead()
{
  return (random(14, 30));
}

float tmsHumedityRead()
{
  return (random(65, 80));
}
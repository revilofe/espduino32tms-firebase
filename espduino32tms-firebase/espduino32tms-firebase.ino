
//Required HTTPClientESP32Ex library to be installed  https://github.com/mobizt/HTTPClientESP32Ex

#include "espduino32tms.h"
#include <WiFi.h>
#include "RealTimeStore.h"

RealTimeStore realTimeStore(PATHFB_OUT, PATHFB_IN);

float temperature = 0.0;
float humedity = 0.0;

// The value will quickly become too large for an int to store
unsigned long previousMillis = 0; // will store last time LED was updated

// Initial definition 1 sg
long interval = 1000; // interval at which to read Humedity & Temperature (milliseconds)

void setup()
{
  Serial.begin(115200);
  connectWIFI();
  realTimeStore.connect(FIREBASE_HOST, FIREBASE_AUTH);
  realTimeStore.setCallback("interval", streamCallback ,streamTimeoutCallback);
}

void loop()
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to read temperature & Humedity; that is, if the difference
  // between the current time and last time you read temperature & Humedity is bigger than
  // the interval at which you want to read temperature & Humedity.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you read Temperature & Humedity
    previousMillis = currentMillis;

    temperature = tmsTemperatureRead();
    humedity = tmsHumedityRead();
    realTimeStore.sendIntValue(TEMPERATURE, temperature);
    realTimeStore.sendIntValue(HUMEDITY, humedity);
  }
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


void streamCallback(streamData data)
{
    long valor =0;
    Serial.println("-------Stream Data1 available-------");
    Serial.println("STREAM PATH: " + data.streamPath());
    Serial.println("PATH: " + data.dataPath());
    Serial.println("TYPE: " + data.dataType());
    Serial.print("VALUE: ");
    if (data.dataType() == "int")
    {
        valor = data.intData();
        if (valor)
        {
          interval = valor;
          Serial.print("Aunmento invervalo... ");
        }
        else
        {
          interval = 0;
          Serial.print("Reseteo invervalo... ");
        }
        Serial.println(valor);          
    }
    else if (data.dataType() == "float")
        Serial.println(data.floatData());
    else if (data.dataType() == "string")
        Serial.println(data.stringData());
    else if (data.dataType() == "json")
        Serial.println(data.jsonData());
    Serial.println();
}

void streamTimeoutCallback()
{
    Serial.println();
    Serial.println("Stream timeout, resume streaming...");
    Serial.println();
}
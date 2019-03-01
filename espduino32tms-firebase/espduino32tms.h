
#include <WiFi.h>
#include "RealTimeStore.h"
#include "LiquidCrystal_I2C.h"
#include "DHTesp.h"
//#include "DHT.h"

//LCD
#define COLUMNAS 16
#define FILAS 2

// WIFI
#define WIFI_SSID "MIWIFI_2G_SP4C"
#define WIFI_PASSWORD "3dh6sjsewpxh"

// DHT
#define DHTPIN 25 
#define DHTTYPE DHTesp::DHT11


// FIREBASE
#define FIREBASE_HOST "espduino32tms.firebaseio.com"
#define FIREBASE_AUTH "QbVSWWQvaLbnNlhxmCJml3iSgsQ6lKtmuq9mfH2R"

#define TOPIC_INTERVAL "interval"
#define TOPIC_TEMPERATURE "temperature"
#define TOPIC_HUMIDITY "humidity"
#define PATHFB_OUT "/dht11-tms"
#define PATHFB_IN "/param-tms"



#define FIREBASE_HOST "espduino32tms.firebaseio.com"
#define FIREBASE_AUTH "QbVSWWQvaLbnNlhxmCJml3iSgsQ6lKtmuq9mfH2R"
#define WIFI_SSID "MIWIFI_2G_SP4C"
#define WIFI_PASSWORD "3dh6sjsewpxh"

#define TEMPERATURE "temperature"
#define HUMEDITY "humedity"
#define PATHFB_OUT "/dht11-tms"
#define PATHFB_IN "/param-tms"

float tmsTemperatureRead();
float tmsHumedityRead();

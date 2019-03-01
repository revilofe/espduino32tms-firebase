
//Required HTTPClientESP32Ex library to be installed  https://github.com/mobizt/HTTPClientESP32Ex

#include "espduino32tms.h"

// Objeto que maneja la conexión con Firebase
RealTimeStore realTimeStore(PATHFB_OUT, PATHFB_IN);

// Objeto para acceder al sensor 
//DHTesp dht(DHTPIN, DHTTYPE);
DHTesp dht;
// Alamacen los valores leidos tras tras consultar a los sensores
int temperature = 0;
int humidity = 0;

// The value will quickly become too large for an int to store
// will store last time Humidity & Temperature was updated
unsigned long previousMillis = 0; 
// Intervalor inicial de 10 sg (10.000) (milliseconds)
long interval = 10000; // interval at which to read Humidity & Temperature (milliseconds)

// LCD
LiquidCrystal_I2C lcd(0x27, COLUMNAS, FILAS);  

void setup()
{
  Serial.begin(115200);
  
  // WIFI
  connectToWIFI();
  
  // LCD
  lcd.init();      // Screen LCD                    
  lcd.backlight(); // Screen LCD

  // DHT11
  dht.setup(DHTPIN, DHTTYPE);
  //dht11.begin(); // Sensor humedad-temperatura

  // FIREBASE
  realTimeStore.connect(FIREBASE_HOST, FIREBASE_AUTH);
  realTimeStore.setCallback(TOPIC_INTERVAL, streamCallback, streamTimeoutCallback);
}

void loop()
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to read temperature & Humidity; that is, if the difference
  // between the current time and last time you read temperature & Humidity is bigger than
  // the interval at which you want to read temperature & Humidity.
  unsigned long currentMillis = millis();

  if ((interval) && (currentMillis - previousMillis >= interval))
  {
    // save the last time you read Temperature & Humidity
    previousMillis = currentMillis;

    // Lee temperatura & humedad
    temperature = getTemperature();
    humidity = getHumidity();

    // Envia los datos leidos a FIREBASE 
    realTimeStore.sendIntValue(TOPIC_TEMPERATURE, temperature);
    realTimeStore.sendIntValue(TOPIC_HUMIDITY, humidity);

    // Pinta en LCD
    pintaLCD();

  }
  
  // Aqui se puede hacer otras cossas que salen fuera del control 
  // establecido en base a interval.
  // ...
}

void connectToWIFI()
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

int getTemperature()
{
  //return (random(14, 30));
  //return dht.readTemperature();
  return dht.getTemperature();

}


int getHumidity()
{
  //return (random(65, 80));
  //return dht.readHumidity();  
  return dht.getHumidity();  
}

void pintaLCD()
{
    lcd.clear(); // Borra pantalla
    lcd.setCursor(0,0); // Inicio del cursor
    lcd.print("H = ");
    lcd.print(humidity);
    lcd.print(";T = ");
    lcd.print(temperature);
    lcd.setCursor(0,1); // Siguiente renglón.
    lcd.print("Interval = ");
    lcd.print(interval);
}


// Callback que es llamada por firebase cuando
// el topic al que se ha subscrito se modifica.
void streamCallback(streamData data)
{
  unsigned long newInterval = 0;
  Serial.println("******** Stream Data1 available ********* ");
  Serial.println("STREAM PATH: " + data.streamPath());
  Serial.println("PATH: " + data.dataPath());
  Serial.println("TYPE: " + data.dataType());
  Serial.print("VALUE: ");
  if (data.dataType() == "int")
  {
    // Cuando se introduce a mano, el valor llega como un entero
    newInterval = data.intData();
    Serial.println(newInterval);
  }
  else if (data.dataType() == "float")
    Serial.println(data.floatData());
  else if (data.dataType() == "string")
  { // Cuando el valor viene de App Inventor, viene como un String y 
    // con el formato "valor". Hay que quitar las comillas para convertirlo
    // a entero.
    String snewInterval = data.stringData();
    //Quita las comillas "" y seguidamente convierte a entero
    snewInterval = snewInterval.substring(1, snewInterval.length() - 1) + "\0";
    newInterval = snewInterval.toInt();
  }
  else if (data.dataType() == "json")
    Serial.println(data.jsonData());
  Serial.println();

  // Recupero el nuevo intervalo
  if (newInterval)
  {
    interval = newInterval;
    Serial.println("Aumento invervalo... " \
        + String(interval));
  }
  else
  {
    // En este caso el nuevo intervalor<=0, por tanto reseteo 
    // los ciclos. No se volverá entrar en el loop hasta interval > 0
    interval = 0;
    previousMillis = 0;
    Serial.println("Reseteo invervalo... " \
        + String(interval));
  }
  pintaLCD();
}

// Callback que se llama cuando salta un timeout
void streamTimeoutCallback()
{
  Serial.println();
  Serial.println("######  Stream timeout, \
      resume streaming...");
  Serial.println();
}
#include <DallasTemperature.h>
#include <SPI.h>
#include "DHT.h"
#include "time.h"
#include <OneWire.h>
#include <PubSubClient.h>
#include <WiFiNINA.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "arduino_secrets.h"

/*Token mqtt*/
#define TOKEN ""

/*sensor humedad ambiente y temperatura*/
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPIN1 0
#define DHTPIN2 1
/*luces*/
#define light_1 2
#define light_2 4
#define light_3 7
#define light_4 8

// Initialize wifi

WiFiClient mkr1010Client;
PubSubClient client(mkr1010Client); //  mqtt client
char ssid[] = SECRET_SSID;        //  your network SSID (name) 
char pass[] = SECRET_PASS;        // your network password 
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;      //connection status
WiFiServer server(80);            //server socket
int WifiStatus = WL_IDLE_STATUS;
long lastReconnectAttempt= 0;
long lastData = 0;
char incomingByte;


// Initialize mqtt
const char mqtt_server[] = "192.168.0.103";        // broker ip
const char publishTopic[] = "microstation";        // Topic to send data
const char Topic[] = "microstation/comunication";  // Topic to recieve data


// Instancia a las clases OneWire y DallasTemperature, sensores de temperatura de agua
OneWire oneWireObjeto(Sensor_Water_Temperature_pin);
DallasTemperature sensorDS18B20(&oneWireObjeto);

// Initialize DHT sensor.

DHT sensor_dht1(DHTPIN1, DHT22);
DHT sensor2_dht2(DHTPIN2, DHT22);

 // Initialize Time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "0.south-america.pool.ntp.org", -10800, 6000);


//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

//time
int Hours= 0; 
int Minutes= 0;
int Seconds= 0;

//time lights automation

int lights_on = 7;
int lights_off = 19;
int coolers_on = 7;
int coolers_low = 22;


// Pin donde se conectan los sensores de temperatura de agua
const int Sensor_Water_Temperature_pin = 3;

/*sensor humedad tierra*/
const float PIN_Sensor_Humedad_1a = A0;
const float PIN_Sensor_Humedad_1b = A1;
const float PIN_Sensor_Humedad_2a = A2;
const float PIN_Sensor_Humedad_2b = A3;

/*Variables para pin de sensores de nivel de agua bandejas*/

const float Pin_Water_tray_level_sensor1 = A4;
const float Pin_Water_tray_level_sensor2 = A5;

/*Electrovalvulas*/

const int Solenoid_Valvule_1 = 7;
const int Solenoid_Valvule_2  = 8;
const int Solenoid_Valvule_3  = 9;
const int Solenoid_Valvule_4  = 10;

/*Bombas de agua*/
const int waterpump_soil = 6;
const int waterpump_hydro = 5;

/*Nivel de agua*/

float  WaterTemp_soil = 0;
float  WaterTemp_Hydro = 0;


/*Variables para guardar datos de sensores de humedad*/

float  Soil_Humidity_Sensor_1a = 0;
float  Soil_Humidity_Sensor_1b = 0;
float  Soil_Humidity_Sensor_2a = 0;
float  Soil_Humidity_Sensor_2b = 0;
float  Water_tray_level_sensor1 = 0;
float  Water_tray_level_sensor2 = 0;

// Variables DHT sensor.

float sensordht1_Temperature;
float sensordht1_Humidity;
float sensordht2_Temperature;
float sensordht2_Humidity;
float Temperature = 0;
float Temperature2 = 0;
float Humidity = 0;
float Humidity2 = 0;


/*variables de tiempo en millis para envio de datos mqtt*/

//unsigned long Timer_now = 0;
unsigned long lastMillis = 0;

void setup() {

  // Iniciamos la comunicación serie
  Serial.begin(115200); 
  Serial1.begin(115200);


 // Iniciamos el reloj con epoch y ntp servers
  timeClient.begin();

  
  Wire.begin(); //(SDA, SCL);
  client.setServer(mqtt_server, 1883);
  client.setCallback (callback);
  lastReconnectAttempt = 0;

  // Iniciamos el bus 1-Wire
  sensorDS18B20.begin();

  //  Iniciamos sensores de humedad ambiente
  sensor_dht1.begin();
  sensor2_dht2.begin();

  // declaramos electrovalvulas como salidas

  pinMode(Solenoid_Valvule_1, OUTPUT);
  pinMode(Solenoid_Valvule_2, OUTPUT);
  pinMode(Solenoid_Valvule_3, OUTPUT);
  pinMode(Solenoid_Valvule_4, OUTPUT);
  pinMode(waterpump_soil, OUTPUT);
  pinMode(waterpump_hydro, OUTPUT);


  // electrovalvulas apagadas
  digitalWrite(Solenoid_Valvule_1,  HIGH);
  digitalWrite(Solenoid_Valvule_2,  HIGH);
  digitalWrite(Solenoid_Valvule_3,  HIGH);
  digitalWrite(Solenoid_Valvule_4,  HIGH);

  // bomba apagada
  digitalWrite(waterpump_soil, HIGH);
  digitalWrite(waterpump_hydro, HIGH);
}

void loop() {
  
printWiFiStatus(); 
Serial.println(WiFi.status());

 if ( WiFi.status() ==  3 )  {
    Serial.print (" internet connected");
    Serial.println(WiFi.status());

// reconect mqtt client
  if (!client.connected()) {
    reconnect();
  }
  
 get_time();
 lights_clycle();
 coolers_clycle();
 hydroponics_irrigation_cycle();
 read_water_temperatures ();
 read_ambient_humidity_temperatures ();
 read_soil_humidity ();

 //publicamos cada 1 hora en el topico usando la funcion millis
  if (millis() - lastMillis > 3600000 ) {
    lastMillis = millis();
    mqtt_message ();
}
    client.loop(); 
    delay(30);
 }
 

    else{
   
 
    mkr1010Client.stop();
    delay (1000);
//    WiFi.disconnect ();
//    delay (1000);
    WiFi.begin(ssid, pass);
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    delay(10000);
  
   }
}


   
    

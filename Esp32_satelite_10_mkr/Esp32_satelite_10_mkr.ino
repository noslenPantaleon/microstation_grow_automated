
#include <SPI.h>
#include <WiFiNINA.h>
#include "time.h"
#include <Adafruit_Sensor.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <ArduinoJson.h>
#define SECRET_SSID "lezica"
#define SECRET_PASS "papicha4132"

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);



const char *mqtt_server = "192.168.0.103";
const int  mqtt_port = 1883;
const char *mqtt_user = "noslen";
const char *mqtt_pass = "100loops";
const char *root_topic_subscribe = "esp32/input";
WiFiClient espClient;
PubSubClient client(espClient);
/*char array mqtt message*/

long count = 0;
char msg[500];

/*sensor humedad ambiente y temperatura*/
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

//DHT Sensor
uint8_t DHTPin = 0;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;
int irrigation1_value=0;

/*Electrovalvulas*/

const int Electro_1 = 1;
const int Electro_2 = 2;
const int Electro_3 = 3;
const int Electro_4 = 4;
const int waterpump_soil = 5;
const int waterpump_hydro = 6;
const int coolers = 16;

/*sensor humedad tierra*/
const float PIN_SENSOR_HUMEDAD_1 = A0;
const float PIN_SENSOR_HUMEDAD_2 = A1;
const float PIN_SENSOR_HUMEDAD_3 = A2;
const float PIN_SENSOR_HUMEDAD_4 = A3;

/*Variables para guardar datos de sensores de humedad de tierra*/

float SHT1 = 0;
float SHT2 = 0;
float SHT3 = 0;
float SHT4 = 0;


/*tiempos de riego*/
//tiempo en milisegundo
int val_1 = 20000;
int val_2 = 10000;
int val_3 = 500000;




String hours;
String minutes;
String seconds;
String days;

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();




void setup() {




  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();   

  Serial.begin(115200);
 

  // electrovalvulas ca
  pinMode(Electro_1, OUTPUT);
  pinMode(Electro_2, OUTPUT);
  pinMode(Electro_3, OUTPUT);
  pinMode(Electro_4, OUTPUT);
  pinMode(coolers,   OUTPUT);
  pinMode(waterpump_soil, OUTPUT);
  pinMode(waterpump_hydro, OUTPUT);

  // sensor humedad ambiente
  pinMode(DHTPin, INPUT);
  dht.begin();

  // electrovalvulas apagadas
  digitalWrite(Electro_1, HIGH);
  digitalWrite(Electro_2, HIGH);
  digitalWrite(Electro_3, HIGH);
  digitalWrite(Electro_4, HIGH);
  // bomba apagada
  digitalWrite(waterpump_soil, HIGH);
  digitalWrite(waterpump_hydro, HIGH);

  // COOLERS ENCENDIDOS
  digitalWrite(coolers, LOW);
}

void loop() {

if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
 }

  
  }
  
  else {
    client.print("\t"); 
     
  }





  
  }




  
  }





 


 // llamamos a la funcion para obtener la hora local
      struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
  }
    delay(1000);

  
  // Convert the timehour to a char array for separeted hour
  char timeHour[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  Serial.print(timeHour);
  Serial.print("\n");

  // Convert the timeMinute to a char array for separeted minutes
  char timeMinute[3];
  strftime(timeMinute, 3, "%M", &timeinfo);
  Serial.print(timeMinute);
  Serial.print("\n");


  // Convert the seconds to a char array for separeted seconds
  char timeSecond[3];
  strftime(timeSecond, 3, "%S", &timeinfo);
  Serial.print(timeSecond);
  Serial.print("\n");

  // Convert the timeweekday to a char array for separeted week
  char timeWeekDay[10];
  strftime(timeWeekDay, 10, "%A", &timeinfo);
  Serial.print(timeWeekDay);
  Serial.print("\n");

  // Convert timeHour and TimeMinute to string for use in a conditional.
  String hours(timeHour);
  String minutes(timeMinute);
  String seconds(timeSecond);
  String days(timeWeekDay);



  // leemos sensor1 y lo guardamos en una variable
  SHT1 = analogRead(PIN_SENSOR_HUMEDAD_1);
  Serial.print("Humedad sensor 1: ");
  Serial.print (SHT1);


  // leemos sensor2 y lo guardamos en una variable
  SHT2 = analogRead(PIN_SENSOR_HUMEDAD_2);
  Serial.print("Humedad sensor 2: ");
  Serial.print (SHT2);


  // leemos sensor3 y lo guardamos en una variable
  SHT3 = analogRead(PIN_SENSOR_HUMEDAD_3);
  Serial.print("Humedad sensor 3: ");
  Serial.print (SHT3);

  // leemos sensor4 y lo guardamos en una variable
  SHT4 = analogRead(PIN_SENSOR_HUMEDAD_4);
  Serial.print("Humedad sensor 4: ");
  Serial.print (SHT4);




  // obtenemos valores de temperatura y humedad y guardamos variables

  Temperature = dht.readTemperature();
  Serial.print("Temperatura ambiente:: ");
  Serial.print (Temperature);
  Serial.print("\n");
  // onbtenemos valores de humedad
  Humidity = dht.readHumidity();
  Serial.print("humedad ambiente:: ");
  Serial.print ( Humidity);
  Serial.print("\n");


  // Convert the sen1value to a char array
  char SHT1_str[8];
  dtostrf(SHT1, 1, 2, SHT1_str);
  //client.publish("esp32/humedad1", SHT1_str);


  // Convert the sen2value to a char array
  char SHT2_str[8];
  dtostrf(SHT2, 1, 2, SHT2_str);
  //client.publish("esp32/humedad2", SHT2_str);


  // Convert the sen3value to a char array
  char SHT3_str[8];
  dtostrf(SHT3, 1, 2, SHT3_str);
  // client.publish("esp32/humedad3", SHT3_str);



  // Convert the sen4value to a char array
  char SHT4_str[8];
  dtostrf(SHT4, 1, 2, SHT4_str);
  //client.publish("esp32/humedad4", SHT4_str);


  // Convert  Humidity the value to a char array
  char   HumiditySTR1[8];
  dtostrf(  Humidity, 1, 2,   HumiditySTR1);
  //client.publish("esp32/humedad ambiente1", HumidityString);


  // Convert   Temperature the value to a char array
  char  TemperatureSTR1[8];
  dtostrf( Temperature, 1, 2,  TemperatureSTR1);
  //client.publish("esp32/temperature1", TemperatureString);


  //****** Riego Tierra********//

  if ((hours) ==  ("10") && (minutes) == ("00") && (seconds) == ("00")) {
    Serial.println("Check value SHT1");
    check_SHT_1();
  
  }

    if ((hours) ==  ("10") && (minutes) == ("01") && (seconds) == ("00")) {
    Serial.println("Check value SHT2");
    check_SHT_2();

  
  }

    if ((hours) ==  ("10") && (minutes) == ("02") && (seconds) == ("00")) {
    Serial.println("Check value SHT3");

    check_SHT_3();
   
  }

    if ((hours) ==  ("10") && (minutes) == ("03") && (seconds) == ("00")) {
    Serial.println("Check value SHT4");

   check_SHT_4();
  }

   if ((hours) ==  ("19") && (minutes) == ("00") && (seconds) == ("00")) {
    Serial.println("Check value SHT1");
    check_SHT_1();
  
  }

    if ((hours) ==  ("19") && (minutes) == ("01") && (seconds) == ("00")) {
    Serial.println("Check value SHT2");
    check_SHT_2();

  
  }

    if ((hours) ==  ("19") && (minutes) == ("02") && (seconds) == ("00")) {
    Serial.println("Check value SHT3");

    check_SHT_3();
   
  }

    if ((hours) ==  ("19") && (minutes) == ("03") && (seconds) == ("00")) {
    Serial.println("Check value SHT4");

   check_SHT_4();
  }
  
  

  else {
    Serial.print("it's not time to check sensors");

  }

  //****** Riego Hidroponia********//


  // hacemos un riego a las 8 am

  if ((hours) ==  ("08") && (minutes) == ("00")) {

    waterpumpon_function ();

  }
    else if ((hours) == ("08") && (minutes)== ("05")){
      
    waterpumpoff_function ();

    }

  if ((hours) ==  ("11") && (minutes) == ("00")) {

  waterpumpon_function ();

}
  else if ((hours) == ("11") && (minutes)== ("05")){
    
  waterpumpoff_function ();

  }  

 if ((hours) ==  ("13") && (minutes) == ("00")) {

  waterpumpon_function ();

}
  else if ((hours) == ("13") && (minutes)== ("05")){
    
  waterpumpoff_function ();

  }

  if ((hours) ==  ("16") && (minutes) == ("00")) {

  waterpumpon_function ();

}
  else if ((hours) == ("16") && (minutes)== ("05")){
    
  waterpumpoff_function ();

  }

  if ((hours) ==  ("19") && (minutes) == ("05")) {

  waterpumpon_function ();

}
  else if ((hours) == ("19") && (minutes)== ("10")){
    
  waterpumpoff_function ();

  }

if ((hours) ==  ("21") && (minutes) == ("00")) {

  waterpumpon_function ();

}
  else if ((hours) == ("21") && (minutes)== ("05")){
    
  waterpumpoff_function ();

  
}
 if ((hours) ==  ("00") && (minutes) == ("00")) {

  waterpumpon_function ();

}
  else if ((hours) == ("00") && (minutes)== ("10")){
    
  waterpumpoff_function ();

  }

   if ((hours) ==  ("02") && (minutes) == ("00")) {

  waterpumpon_function ();

}
  else if ((hours) == ("02") && (minutes)== ("10")){
    
  waterpumpoff_function ();

  }

  
  else
  {

 Serial.print("hydroponics pump off");
    
  }

  
  //json message//

  //creamos el documento json
  //DynamicJsonDocument doc(1024);
  StaticJsonDocument<300> doc;


  // creamos los objectos json


  JsonObject rack1 = doc.createNestedObject("rack1");
  rack1["HA1"] = HumiditySTR1;
  rack1["TA_1"] = TemperatureSTR1;
  rack1["SHT_1"] = SHT1_str;
  rack1["SHT_2"] = SHT2_str;
  rack1["SHT_3"] = SHT3_str;
  rack1["SHT_4"] = SHT4_str;


  //almacena el json en un buffer para enviar por mqttt

  char buffer[256];
  serializeJson(doc, buffer);
  client.publish ("esp32/satelitegrow", buffer);

  client.loop();

}

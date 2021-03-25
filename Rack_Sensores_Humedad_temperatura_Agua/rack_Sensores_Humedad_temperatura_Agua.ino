
#include "DHT.h"


/*sensor humedad ambiente y temperatura*/
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321




// Initialize DHT sensor.

DHT sensor_dht1(1, DHT22);  
DHT sensor2_dht2(2, DHT22); 

// Variables DHT sensor.

float sensordht1_Temperature;
float sensordht1_Humidity;
float sensordht2_Temperature;
float sensordht2_Humidity;
float Temperature =0;
float Temperature2 =0;
float Humidity =0;
float Humidity2 = 0;




void setup() {

Serial.begin(115200);

  // sensors humedad ambiente
  sensor_dht1.begin();
  sensor2_dht2.begin();

}

void loop() {


  // obtenemos valores de temperatura y humedad y guardamos variables

  Temperature = sensor_dht1.readTemperature();
  Serial.print("Temperatura ambiente:: ");
  Serial.print (Temperature);
  Serial.print("\t");
  // onbtenemos valores de humedad
  Humidity = sensor_dht1.readHumidity();
  Serial.print("humedad ambiente:: ");
  Serial.print ( Humidity);
  

   delay(500);

// obtenemos valores de temperatura2 y humedad2 y guardamos variables

  Temperature2 = sensor2_dht2.readTemperature(1);
  Serial.print("Temperatura ambiente2:: ");
  Serial.print (Temperature2);
  Serial.print("\t");
  // onbtenemos valores de humedad
  Humidity2 = sensor2_dht2.readHumidity(1);
  Serial.print("humedad ambiente2:: ");
  Serial.print ( Humidity2);
  Serial.print("\n");

 delay(500);
  

 

}

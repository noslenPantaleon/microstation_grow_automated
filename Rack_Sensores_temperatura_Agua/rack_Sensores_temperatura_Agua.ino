#include <OneWire.h> 
#include <DallasTemperature.h>
const int ONE_WIRE_BUS = 3; 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
const float watertemp_Hydro;

void setup() {

Serial.begin(115200);


  

}

void loop() {

 // obtenemos valores de temperatura agua hidroponia y guardamos variables
 
 sensors.requestTemperatures(); // Send the command to get temperature readings 

    Serial.print("Temperatura del agua hidroponica: ");
    Serial.print("\t"); 
    Serial.print(sensors.getTempCByIndex(0));
    watertemp_Hydro = sensors.getTempCByIndex(0);
    Serial.print("\t"); 
   Serial.print(" Celsius");
    Serial.print("\t"); 
    //Serial.print("\n");

    delay(500);
 
  

 

}

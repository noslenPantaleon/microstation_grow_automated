

const float PIN_Sensor_Humedad_1a = A0;
const float PIN_Sensor_Humedad_1b = A1;
const float PIN_Sensor_Humedad_2a = A2;
const float PIN_Sensor_Humedad_2b = A3;
const float PIN_Sensor_Nivel_Agua_1 = A4;
const float PIN_Sensor_Nivel_Agua_2 = A5;
float  Sensor_Humedad_1a = 0;
float  Sensor_Humedad_1b = 0;
float  Sensor_Humedad_2a = 0;
float  Sensor_Humedad_2b = 0;
float  Sensor_Nivel_Agua1 = 0;
float  Sensor_Nivel_Agua2 = 0;


void setup() {



}

void loop() {
  // put your main code here, to run repeatedly:

  // leemos sensor1 y lo guardamos en una variable

  Sensor_Humedad_1a = analogRead(PIN_Sensor_Humedad_1a);
  Serial.print("Sensor_Humedad_1a: ");

  Serial.print (Sensor_Humedad_1a);
  Serial.print("\t");

  // leemos sensor2 y lo guardamos en una variable

  Sensor_Humedad_1b = analogRead(PIN_Sensor_Humedad_1b);
  Serial.print("Sensor_Humedad_1b ");

  Serial.print ( Sensor_Humedad_1b);
  Serial.print("\t");


  // leemos sensor3 y lo guardamos en una variable
  Sensor_Humedad_2a = analogRead(PIN_Sensor_Humedad_2a);

  Serial.print("Sensor_Humedad_2a: ");

  Serial.print (  Sensor_Humedad_2a);
  Serial.print("\t");
  


  // leemos sensor4 y lo guardamos en una variable

  Sensor_Humedad_2b = analogRead(PIN_Sensor_Humedad_2b);
  Serial.print("Sensor_Humedad_2b: ");

  Serial.print (Sensor_Humedad_2b);
  Serial.print("\t");


  Sensor_Nivel_Agua1 = analogRead(PIN_Sensor_Nivel_Agua_1);
  Serial.print("Sensor_Nivel_Agua1: ");
  Serial.print (Sensor_Nivel_Agua1);
  Serial.print("\t");


  Sensor_Nivel_Agua2 = analogRead(PIN_Sensor_Nivel_Agua_2);
  Serial.print("Sensor_Nivel_Agua2: ");
  Serial.print (Sensor_Nivel_Agua2);
  Serial.print("\t");

  delay (1000);

  Serial.print("\n");


}

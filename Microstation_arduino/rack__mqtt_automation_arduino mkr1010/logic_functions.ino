
void waterpumpon_function () {

  digitalWrite(waterpump_hydro, LOW);
  return;
}

void waterpumpoff_function () {
  digitalWrite(waterpump_hydro, HIGH);

  return;

}


void irrigation_sensor_1a () {

  int periodo = 10000;
  unsigned long TiempoAhora = 0;

  digitalWrite(waterpump_soil, LOW);
  digitalWrite(Solenoid_Valvule_1 , LOW);

  TiempoAhora = millis();
  while (millis() < TiempoAhora + periodo) {

  }

  digitalWrite(waterpump_soil, HIGH);
  digitalWrite(Solenoid_Valvule_1 , HIGH);

  return;

}

void irrigation_sensor_1b () {

  int periodo = 10000;
  unsigned long TiempoAhora = 0;

  digitalWrite(waterpump_soil, LOW);
  digitalWrite(Solenoid_Valvule_2 , LOW);


  TiempoAhora = millis();
  while (millis() < TiempoAhora + periodo) {

  }


  digitalWrite(waterpump_soil, HIGH);
  digitalWrite(Solenoid_Valvule_2 , HIGH);

  return;
}


void irrigation_sensor_2a () {

  int periodo = 10000;
  unsigned long TiempoAhora = 0;

  digitalWrite(waterpump_soil, LOW);
  digitalWrite(Solenoid_Valvule_3 , LOW);


  TiempoAhora = millis();
  while (millis() < TiempoAhora + periodo) {

  }

  digitalWrite(waterpump_soil, HIGH);
  digitalWrite(Solenoid_Valvule_3 , HIGH);

  return;


}
void irrigation_sensor_2b () {

  int periodo = 10000;
  unsigned long TiempoAhora = 0;

  digitalWrite(waterpump_soil, LOW);
  digitalWrite(Solenoid_Valvule_4 , LOW);


  TiempoAhora = millis();
  while (millis() < TiempoAhora + periodo) {

  }

  digitalWrite(waterpump_soil, HIGH);
  digitalWrite(Solenoid_Valvule_4 , HIGH);

  return;
}

void check_Soil_Humidity_Sensor_1a() {

  if  ( Soil_Humidity_Sensor_1a  >= 2200 &&  Soil_Humidity_Sensor_1a  <= 3300) {
    irrigation_sensor_1a ();
  }
  else {
   return;
  }
}

void check_Soil_Humidity_Sensor_1b() {

  if  ( Soil_Humidity_Sensor_1b  >= 2200 && Soil_Humidity_Sensor_1b <= 3300) {
    irrigation_sensor_1b ();
  }
  else {
   return;
  }
}

void check_Soil_Humidity_Sensor_2a() {

  if ( Soil_Humidity_Sensor_2a  >= 2200 &&  Soil_Humidity_Sensor_2a  <= 3300) {
    irrigation_sensor_2a();
  }
  else {
    return;
  }
}


void check_Soil_Humidity_Sensor_2b()  {

  if ( Soil_Humidity_Sensor_2b  >= 2200 &&  Soil_Humidity_Sensor_2b  <= 3300) {
    irrigation_sensor_2b ();
  }

  else {
   return;
  }
}


void enable_WiFi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
  return;
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

}

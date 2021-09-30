

// get time npt epoch
void get_time() {

  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);

  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);

  Hours = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(Hours);

  Minutes = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(Minutes);

  Seconds = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(Seconds);

  String weekDay = weekDays[timeClient.getDay()];
  Serial.print("Week Day: ");
  Serial.println(weekDay);

  //Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon + 1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  String currentMonthName = months[currentMonth - 1];
  Serial.print("Month name: ");
  Serial.println(currentMonthName);

  int currentYear = ptm->tm_year + 1900;
  Serial.print("Year: ");
  Serial.println(currentYear);

  //Print complete date:
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  Serial.print("Current date: ");
  Serial.println(currentDate);
  Serial.println("");

  delay(1000);

}




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


//  //****** ciclo encendido luces********//

void lights_clycle () {

  if (Hours > lights_on && Hours < lights_off) {
    Serial1.write('L');
  }

  else {
    Serial1.write('H');
  }
}

//  //****** ciclo encendido coolers********//

void coolers_clycle () {

  if (Hours > coolers_on && Hours < coolers_low) {
    // envia mensaje serial a arduino uno y enciende ventilacion
    Serial1.write('z');
  }

  else if ( Humidity < 40 ) {
    // envia mensaje serial a arduino uno y  apaga ventilacion
    Serial1.write('x');
  }

  else {
    // envia mensaje serial a arduino uno y pone en nivel medio la ventilacion
    Serial1.write('y');
  }


}


//****** Riego Hidroponia********//

void hydroponics_irrigation_cycle () {

  // hacemos un riego de 6 minutos cada 2 horas

  if (Hours == 8 && Minutes == 00) {
    waterpumpon_function ();
    // envia mensaje serial a arduino uno y enciende ventilacion al maximo

  }

  else if (Hours == 8 &&  Minutes == 05) {
    waterpumpoff_function ();
  }


  if (Hours == 10 && Minutes == 00) {
    waterpumpon_function ();
  }

  else if (Hours == 10 &&  Minutes == 05) {
    waterpumpoff_function ();
  }


  if (Hours == 12 && Minutes == 00) {
    waterpumpon_function ();
  }

  else if (Hours == 12 &&  Minutes == 05) {
    waterpumpoff_function ();
  }

  if (Hours == 14 && Minutes == 00) {
    waterpumpon_function ();
  }

  else if (Hours == 14 &&  Minutes == 05) {
    waterpumpoff_function ();
  }


  if (Hours == 16 && Minutes == 00) {
    waterpumpon_function ();
  }

  else if (Hours == 16 &&  Minutes == 05) {
    waterpumpoff_function ();
  }


  if (Hours == 18 && Minutes == 00) {
    waterpumpon_function ();
  }

  else if (Hours == 18 &&  Minutes == 05) {
    waterpumpoff_function ();
  }


  if (Hours == 20 && Minutes == 00) {
    waterpumpon_function ();
  }

  else if (Hours == 20 &&  Minutes == 05) {
    waterpumpoff_function ();
  }


  if (Hours == 22 && Minutes == 00) {
    waterpumpon_function ();
  }

  else if (Hours == 22 &&  Minutes == 05) {
    waterpumpoff_function ();
    // envia mensaje serial a arduino uno y  pone ventilacion en nivel bajo
    Serial1.write('y');

  }


  if (Hours == 00 && Minutes == 00) {
    waterpumpon_function ();
  }

  else if (Hours == 00 &&  Minutes == 05) {
    waterpumpoff_function ();
  }


  if (Hours == 2 && Minutes == 00) {
    waterpumpon_function ();
  }

  else if (Hours == 2 &&  Minutes == 05) {
    waterpumpoff_function ();
  }


  if (Hours == 4 && Minutes == 00) {
    waterpumpon_function ();
  }

  else if (Hours == 4 &&  Minutes == 05) {
    waterpumpoff_function ();
  }


  if (Hours == 6 && Minutes == 00) {
    waterpumpon_function ();
  }

  else if (Hours == 6 &&  Minutes == 05) {
    waterpumpoff_function ();
  }

}

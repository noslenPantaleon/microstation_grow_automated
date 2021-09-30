

void read_water_temperatures (){
  
  // Leemos y mostramos los datos de los sensores de temperatura de agua DS18B20

  sensorDS18B20.requestTemperatures();

  WaterTemp_soil  = sensorDS18B20.getTempCByIndex(0);

  WaterTemp_Hydro = sensorDS18B20.getTempCByIndex(1);

}



void read_ambient_humidity_temperatures (){


  // obtenemos valores de temperatura y humedad y guardamos variables

  Temperature = sensor_dht1.readTemperature();
  
  // onbtenemos valores de humedad
  Humidity = sensor_dht1.readHumidity();
  


  // obtenemos valores de temperatura2 y guardamos variables

  Temperature2 = sensor2_dht2.readTemperature(1);


  // onbtenemos valores de humedad2 y guardamos variables

  Humidity2 = sensor2_dht2.readHumidity(1);

}

void read_soil_humidity (){

  // configuramos la resolución de lectura analogica a 12 bits.
  analogReadResolution(12);

  // leemos sensor1 y lo guardamos en una variable

  Soil_Humidity_Sensor_1a = analogRead(PIN_Sensor_Humedad_1a);

  // leemos sensor2 y lo guardamos en una variable

  Soil_Humidity_Sensor_1b = analogRead(PIN_Sensor_Humedad_1b);


  // leemos sensor3 y lo guardamos en una variable
  Soil_Humidity_Sensor_2a = analogRead(PIN_Sensor_Humedad_2a);


  // leemos sensor4 y lo guardamos en una variable

  Soil_Humidity_Sensor_2b = analogRead(PIN_Sensor_Humedad_2b);


  // leemos sensor de nivel de agua_1 bandejas y lo guardamos en una variable

  Water_tray_level_sensor1 = analogRead(Pin_Water_tray_level_sensor1);


  // leemos sensor de nivel de agua_2 bandejas y lo guardamos en una variable

  Water_tray_level_sensor2 = analogRead( Pin_Water_tray_level_sensor2 );

}

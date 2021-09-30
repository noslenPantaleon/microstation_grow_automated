
void reconnect() {

  long checkNow = millis();
    if (checkNow - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = checkNow;    
  client.setServer(mqtt_server, 1883);
  client.setCallback (callback);

  while (!client.connected()) {

    Serial.print("Attempting MQTT connection ....");

    if (client.connect("ClientID", TOKEN, NULL)) {
      Serial.println("Connected to MQTT Broker");
      client.subscribe( Topic);
      Serial.print("Subcribed to: ");
      Serial.println(Topic);
      Serial.println('\n');
      
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 second");
      digitalWrite(LED_BUILTIN, LOW);
      lastReconnectAttempt = 0;
    }
  }

}

}


void callback(char* Topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(Topic);
  Serial.print(". Message: ");
  String message_arrived;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    message_arrived += (char)message[i];
  }
  Serial.println();

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message

  if (String(Topic) == "microstation/comunication") {

    if (message_arrived  == "lights_on") {
      Serial1.write('L');
      
    }

    if (message_arrived == "lights_off") {
      Serial1.write('H');
      
    }

    if (message_arrived == "light1_on") {
      Serial1.write('q');
    }

    if (message_arrived == "light2_on") {
      Serial1.write('w');
    }

    if (message_arrived == "light3_on") {
      Serial1.write('e');
    }

    if (message_arrived == "light4_on") {
      Serial1.write('r');
    }

    if (message_arrived == "light1_off") {
      Serial1.write('a');
    }

    if (message_arrived == "light2_off") {
      Serial1.write('s');
    }

    if (message_arrived == "light3_off") {
      Serial1.write('d');
    }

    if (message_arrived == "light4_off") {
      Serial1.write('f');
    }

    if (message_arrived == "Coolers_on") {
      Serial1.write('z');
    }

        if (message_arrived == "Coolers_mid") {
      Serial1.write('y');
    }

    if (message_arrived == "Coolers_off") {
      Serial1.write('x');
    }

    if (message_arrived == "irrigation_1a") {
      irrigation_sensor_1a ();
    }

    if (message_arrived == "irrigation_1b") {
      irrigation_sensor_1b ();
    }

    if (message_arrived == "irrigation_2a") {
      irrigation_sensor_2a ();
    }

    if (message_arrived == "irrigation_2b") {
      irrigation_sensor_2b ();
    }

    if (message_arrived == "waterpump_on") {
      waterpumpon_function ();
    }

    if (message_arrived == "waterpump_off") {
      waterpumpoff_function ();
    }
       if (message_arrived == "send_data") {
       mqtt_message ();
    }
  }
}


void mqtt_message (){

  // Convert the sensor values to string

  String Soil_humidity_1a  = String( Soil_Humidity_Sensor_1a );
  String Soil_humidity_1b  = String( Soil_Humidity_Sensor_1b );
  String Soil_humidity_2a  = String( Soil_Humidity_Sensor_2a );
  String Soil_humidity_2b  = String( Soil_Humidity_Sensor_2b );
  String Ambient_humidity1  = String(Humidity);
  String Ambient_humidity2  = String(Humidity2);
  String Ambient_Temperature1  = String(Temperature);
  String Ambient_Temperature2  = String(Temperature2);
  String Water_Temperature_Microgreens = String(WaterTemp_soil );
  String Water_Temperature_Hydroponics = String(WaterTemp_Hydro);
  String Water_level_Tray_1 = String(Water_tray_level_sensor1);
  String Water_level_Tray_2  = String(Water_tray_level_sensor2);


  //json message//

  //creamos el documento json
  DynamicJsonDocument doc(1024);

  // creamos los objectos json
  JsonObject rack1 = doc.createNestedObject("rack1");
  rack1["AH1"]  = Ambient_humidity1;
  rack1["AH2"] = Ambient_humidity2;
  rack1["AT1"] = Ambient_Temperature1;
  rack1["AT2"] = Ambient_Temperature2;
  rack1["WTM"]  =Water_Temperature_Microgreens;
  rack1["WTH"] = Water_Temperature_Hydroponics;
  rack1["WLT1"] = Water_level_Tray_1;
  rack1["WLT2"] = Water_level_Tray_2;
  rack1["SH1a"] = Soil_humidity_1a;
  rack1["SH1b"] = Soil_humidity_1b;
  rack1["SH2a"] = Soil_humidity_2a;
  rack1["SH2b"] = Soil_humidity_2b;


  //almacena el json en un buffer para enviar por mqttt
  char buffer[256];
  size_t n =  serializeJson(doc, buffer);
  client.publish (publishTopic, buffer, n);
  return; 
  }
  




//****** Programas lecturas de sensores y riego********//  


 void waterpumpon_function (){ 
  
  digitalWrite(waterpump_hydro, LOW);
  Serial.println("hydroponic pump on");
  client.publish("esp32/notificaciones",  "hydroponic pump on");
   }

 void waterpumpoff_function (){ 
 digitalWrite(waterpump_hydro, HIGH);
  client.publish("esp32/notificaciones",  "hydroponic pump off"); 
 return;
 }



void check_SHT_1(){
  
  if  (SHT1 >= 2200 && SHT1 <= 3300) {
    digitalWrite(waterpump_soil, LOW);
    digitalWrite(Electro_1, LOW);
    Serial.print("irrigation1 in process");
    client.publish("esp32/notificaciones",  "irrigation1 in process");
    delay(val_1);
    digitalWrite(waterpump_soil, HIGH); 
    digitalWrite(Electro_1, HIGH);
    Serial.println("rirrigation1 done");
    client.publish("esp32/notificaciones",  "irrigation1 done");
 }
    
  else {
    Serial.println("humidity1 ok");
    client.publish("esp32/notificaciones",  "humidity1 ok");
    return;   
         }
     }      
 


void check_SHT_2() {
  
  if  (SHT2 >= 2200 && SHT2 <= 3300) {
    
    digitalWrite(waterpump_soil, LOW);
    digitalWrite(Electro_2, LOW);
    Serial.print("irrigation2 in process");
    client.publish("esp32/notificaciones",  "irrigation2 in process");
    delay(val_1);
    digitalWrite(waterpump_soil, HIGH);
    digitalWrite(Electro_2, HIGH);
    Serial.println("irrigation2 done");
     client.publish("esp32/notificaciones",  "irrigation2 done");
      }
  else {
    Serial.println("humidity2 ok");
    client.publish("esp32/notificaciones",  "humidity2 ok");
    return;   
    }
      
           }
        
void check_SHT_3() {
    
  if (SHT3 >= 2200 && SHT3 <= 3300) {
      digitalWrite(waterpump_soil, LOW);
      digitalWrite(Electro_3, LOW);
      Serial.print("irrigation3 in process");
      client.publish("esp32/notificaciones",  "irrigation3 in process");
      delay(val_1);
      digitalWrite(waterpump_soil, HIGH);
      digitalWrite(Electro_3, HIGH);
      Serial.println("irrigation3 done");
      client.publish("esp32/notificaciones",  "irrigation3 done");
    }  
   else {
      Serial.println("humidity3 ok");
      client.publish("esp32/notificaciones",  "humidity3 ok");
      return;   
    }    
  }
        
       

void check_SHT_4()  {

  if (SHT1 >= 2200 && SHT1 <= 3300) {
    digitalWrite(waterpump_soil, LOW);
    digitalWrite(Electro_4, LOW);
    Serial.print("irrigation4 in process");
    client.publish("esp32/notificaciones",  "irrigation4 in process");
    delay(val_1);
    digitalWrite(waterpump_soil, HIGH);
    digitalWrite(Electro_4, HIGH);
    Serial.println("irrigation4 done");
    client.publish("esp32/notificaciones",  "irrigation4 done");
    }
    
  else {
     Serial.println("humidity4 ok");
     client.publish("esp32/notificaciones",  "humidity4 ok");
     return;   
      }
    }
  

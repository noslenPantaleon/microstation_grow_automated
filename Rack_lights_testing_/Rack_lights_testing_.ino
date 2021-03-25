

int light_1 = 2;
int light_2 = 4;
int light_3 = 7;
int light_4 = 8;
char incomingByte;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  
  Serial.begin(115200);

  pinMode(light_1, OUTPUT);
  pinMode(light_2, OUTPUT);
  pinMode(light_3, OUTPUT);
  pinMode(light_4, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {



  // read the oldest byte in the serial buffer:
  
  if (Serial.available ()> 0 ) {
  incomingByte = Serial.read();

  if (incomingByte == 'H')
  {
    Serial.print('H');

    digitalWrite(light_1, HIGH);
    digitalWrite(light_2, HIGH);
    digitalWrite(light_3, HIGH);
    digitalWrite(light_4, HIGH);
   

  }
 
  
  
  if (incomingByte == 'L')
  {
    Serial.print('L');
    digitalWrite(light_1, LOW);
    digitalWrite(light_2, LOW);
    digitalWrite(light_3, LOW);
    digitalWrite(light_4, LOW);
  }
    }

  Serial.print (incomingByte);








}
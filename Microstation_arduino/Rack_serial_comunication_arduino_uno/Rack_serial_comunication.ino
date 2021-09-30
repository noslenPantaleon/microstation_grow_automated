int pwmPin  = 3; // digital PWM pin 9
int pwmVal  = 1; // The PWM Value
int light_1 = 4;
int light_2 = 7;
int light_3 = 8;
int light_4 = 12;
unsigned long time;
unsigned int rpm;
String stringRPM;
char incomingByte;


void setup() {

  Serial.begin(115200);

  getRPMS();
  delay(200);
  int val2 = 79;
  OCR2B = val2;

  //set lights pins
  pinMode(light_2, OUTPUT);
  pinMode(light_3, OUTPUT);
  pinMode(light_4, OUTPUT);

  //set lights turn off
  digitalWrite(light_1, HIGH);
  digitalWrite(light_2, HIGH);
  digitalWrite(light_3, HIGH);
  digitalWrite(light_4, HIGH);

  // generate 25kHz PWM pulse rate on Pin 3
  pinMode(pwmPin, OUTPUT);        // OCR2B sets duty cycle
  // Set up Fast PWM on Pin 3
  TCCR2A = 0x23;                  // COM2B1, WGM21, WGM20
  TCCR2B = 0x0A;                  // WGM21, Prescaler = /8
  OCR2A = 79;                     // TOP DO NOT CHANGE, SETS PWM PULSE RATE
  OCR2B = 0;                      // duty cycle for Pin 3 (0-79) generates 1 500nS pulse even when 0 :
  digitalWrite(2, HIGH);          // Starts reading
}

void loop() {

  getRPMS();
  delay(200);

  // read serial port with incoming data:
  if (Serial.available () > 0 ) {
    delay(100) ;
  }
  incomingByte = Serial.read();

  // set conditionals on recieved data

  // turn on cooler with maximun pwm revolutions
  if (incomingByte == 'z'){
    int val = 79;
    OCR2B = val;
  }

  // turn on cooler with mid level pwm revolutions
  if (incomingByte == 'y'){
    int val2 = 40;
    OCR2B = val2;
  }


  // turn off coolers
  if (incomingByte == 'x'){
    int val2 = 10;
    OCR2B = val2;
  }

  // turn of lights
  if (incomingByte == 'H'){
    digitalWrite(light_1, HIGH);
    digitalWrite(light_2, HIGH);
    digitalWrite(light_3, HIGH);
    digitalWrite(light_4, HIGH);
  }

  if (incomingByte == 'a'){ 
    digitalWrite(light_1, HIGH);
  }

  if (incomingByte == 's'){
    digitalWrite(light_2, HIGH);
  }

  if (incomingByte == 'd') {
   digitalWrite(light_3, HIGH);
   }

  if (incomingByte == 'f'){
   digitalWrite(light_4, HIGH);
  }


  //encendido de luces
  if (incomingByte == 'L'){
    digitalWrite(light_1, LOW);
    digitalWrite(light_2, LOW);
    digitalWrite(light_3, LOW);
    digitalWrite(light_4, LOW);
  }

  if (incomingByte == 'q'){
   digitalWrite(light_1, LOW);
  }

  if (incomingByte == 'w'){
    digitalWrite(light_2, LOW);
  }

  if (incomingByte == 'e'){
    digitalWrite(light_3, LOW);
  }

  if (incomingByte == 'r'){
    digitalWrite(light_4, LOW);
  }

}


char getRPMS() {
  time = pulseIn(2, HIGH);
  rpm = (1000000 * 60) / (time * 4);
  stringRPM = String(rpm);
  if (stringRPM.length() < 5) {
    //    Serial.println(rpm, DEC);
  }

}

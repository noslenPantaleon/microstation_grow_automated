

int light_1 = 2;
int light_2 = 4;
int light_3 = 7;
int light_4 = 8;

word salidaPwm_1 = 6;
word salidaPwm_2 = 9;
word salidaPwm_3 = 10;
word salidaPwm_4 = 11;
int valor = 0;
int valorPwm = 0;
double pulso = 0;
double pulso_2 = 0;
double frecuencia = 0;


char incomingByte;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.

  Serial.begin(115200);

  pinMode(light_1, OUTPUT);
  pinMode(light_2, OUTPUT);
  pinMode(light_3, OUTPUT);
  pinMode(light_4, OUTPUT);

  pinMode(salidaPwm_1, OUTPUT);
  pinMode(salidaPwm_2, OUTPUT);
  pinMode(salidaPwm_3, OUTPUT);
  pinMode(salidaPwm_4, OUTPUT);


  digitalWrite(light_1, HIGH);
  digitalWrite(light_2, HIGH);
  digitalWrite(light_3, HIGH);
  digitalWrite(light_4, HIGH);

  configura25KhzPwm();

}

// the loop function runs over and over again forever
void loop() {



  // read the oldest byte in the serial buffer:

  if (Serial.available () > 0 ) {
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




  cicloPwm(00); // 25% (range = 0-79 = 1.25-100%)
  delay(15000);

  cicloPwm(79); // 75% (range = 0-79 = 1.25-100%)
  delay (15000);
  medirRPM();



}



void configura25KhzPwm() {
  TCCR2A = 0;                                               // TC2 Control Register A
  TCCR2B = 0;                                               // TC2 Control Register B
  TIMSK2 = 0;                                               // TC2 Interrupt Mask Register
  TIFR2 = 0;                                                // TC2 Interrupt Flag Register
  TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);    // OC2B cleared/set on match when up/down counting, fast PWM
  TCCR2B |= (1 << WGM22) | (1 << CS21);                     // prescaler 8
  OCR2A = 79;                                               // TOP overflow value (Hz)
  OCR2B = 0;
}

void cicloPwm(byte ocrb) {
  OCR2B = ocrb;                                            // PWM Width (duty)
}

void medirRPM() {
  pulso = pulseIn(3, HIGH);
//  pulso_2 = pulseIn(5, HIGH);


}

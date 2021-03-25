word salidaPwm_1 = 6;
word salidaPwm_2 = 9;
word salidaPwm_3 = 10;
word salidaPwm_4 = 11;
int potenciometro = A0;
int valor = 0;
int valorPwm = 0;
double pulso = 0;
double pulso_2 = 0;
double frecuencia = 0;

void setup() {
  pinMode(salidaPwm_1, OUTPUT);
  pinMode(salidaPwm_2, OUTPUT);
  pinMode(salidaPwm_3, OUTPUT);
  pinMode(salidaPwm_4, OUTPUT);
  pinMode(potenciometro, INPUT);
  configura25KhzPwm();
  Serial.begin(115200);
}

void loop() {

  //valor=analogRead(potenciometro);
  //valorPwm=map(valor,0,1023,0,79);
  // cicloPwm(valorPwm);
  //  Serial.println(valorPwm);
  cicloPwm(10); // 25% (range = 0-79 = 1.25-100%)
  delay(15000);

  cicloPwm(39); // 50% (range = 0-79 = 1.25-100%)
  delay (15000);
  cicloPwm(59); // 75% (range = 0-79 = 1.25-100%)
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
  pulso_2 = pulseIn(5, HIGH);
 

}

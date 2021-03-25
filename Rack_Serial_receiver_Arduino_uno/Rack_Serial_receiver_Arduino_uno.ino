const int ledPin = 13; // the pin that the LED is attached to
char incomingByte;      // a variable to read incoming serial data into

int light_1 = 2;
int light_2 = 4;
int light_3 = 7;
int light_4 = 8;

void setup() {
  // initialize serial communication:
  Serial.begin(115200);
  // initialize the LED pin as an output:

  pinMode(light_1, OUTPUT);
  pinMode(light_2, OUTPUT);
  pinMode(light_3, OUTPUT);
  pinMode(light_4, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // see if there's incoming serial data:
  if (Serial.available() > 0)
  {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'H')
    {
      digitalWrite(light_1, HIGH);
      digitalWrite(light_2, HIGH);
      digitalWrite(light_3, HIGH);
      digitalWrite(light_4, HIGH);

      digitalWrite(ledPin, HIGH);
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L')
    {
      digitalWrite(light_1, LOW);
      digitalWrite(light_2, LOW);
      digitalWrite(light_3, LOW);
      digitalWrite(light_4, LOW);
      digitalWrite(ledPin, LOW);
    }

    Serial.print (incomingByte);
  }

  Serial.print('1');
  delay(500);
  Serial.print('0');
  delay(500);
}

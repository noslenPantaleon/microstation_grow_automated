int ledPin = 6;
char incomingByte; 

void setup()
{
  uint32_t baudRate =  115200;
  Serial1.begin(baudRate);
}

void loop()
{
  Serial1.print('H');
  delay(2000);
  Serial1.print('L');
  delay(2000);



 // read the oldest byte in the serial buffer:
    incomingByte = Serial1.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == '1')
    {
      digitalWrite(ledPin, HIGH);
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == '0')
    {
      digitalWrite(ledPin, LOW);
    }

    Serial.print (incomingByte);

  
}

#include <SPI.h>

#include <WiFiNINA.h> //Include this instead of WiFi101.h as needed
#include <WiFiUdp.h>
#include <RTCZero.h>

RTCZero rtc;

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "lezica";        // your network SSID (name)
char pass[] = "papicha4132";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                           // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

const int GMT = -4; //change this to adapt it to your time zone

int Hours;
int Minutes;
int Seconds;


void setup() {

  Serial.begin(115200);

  // check if the WiFi module works

  if (WiFi.status() == WL_NO_SHIELD) {

    Serial.println("WiFi shield not present");

    // don't continue:

    while (true);

  }

  // attempt to connect to WiFi network:

  while ( status != WL_CONNECTED) {

    Serial.print("Attempting to connect to SSID: ");

    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:

    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:

    delay(10000);

  }

  // you're connected now, so print out the status:

  printWiFiStatus();

  rtc.begin();

  unsigned long epoch;

  int numberOfTries = 0, maxTries = 6;

  do {

    epoch = WiFi.getTime();

    numberOfTries++;

  }

  while ((epoch == 0) && (numberOfTries < maxTries));

  if (numberOfTries == maxTries) {

    Serial.print("NTP unreachable!!");

    while (1);

  }

  else {

    Serial.print("Epoch received: ");

    Serial.println(epoch);

    rtc.setEpoch(epoch);

    Serial.println();

  }
}

void loop() {

//  printDate();

  printTime();

  Serial.println();

   delay(2000);

//  // Convert the timehour to a char array for separeted hour
//  char timeHour[3];
//  strftime(timeHour, 3, rtc.getHours());
//  Serial.print(timeHour);
//  Serial.print("\n");
//
//  // Convert the timeMinute to a char array for separeted minutes
//  char timeMinute[3];
//  strftime(timeMinute, 3, rtc.getMinutes());
//  Serial.print(timeMinute);
//  Serial.print("\n");
//
//
//  // Convert the seconds to a char array for separeted seconds
//  char timeSecond[3];
//  strftime(timeSecond, 3, rtc.getSeconds()
//);
//  Serial.print(timeSecond)
;
//  Serial.print("\n");


//int Hours= (rtc.getHours() + GMT);
//int Minutes= (rtc.getMinutes());
//int Seconds= (rtc.getSeconds());




// String hours ( Hours);
// String minutes (Minutes);
// String seconds ( Seconds);

  
//      if (Hours ==22 && Minutes == 36 &&   Seconds== 40) {
//    Serial.println("Check value SHT2");
//}
//      if (Hora ==  ("19") && Minutes == ("47") && Seconds == ("00")) {
//    Serial.println("Check value SHT2");


//Serial.print (Hours);
//Serial.print("\n");
//Serial.print(Minutes );
//Serial.print("\n");
//Serial.print (Seconds );





}

void printTime()
{

  print2digits(rtc.getHours() + GMT);

  Serial.print(":");

  print2digits(rtc.getMinutes());

  Serial.print(":");

  print2digits(rtc.getSeconds());

  Serial.println();
}

void printDate()
{

  Serial.print(rtc.getDay());

  Serial.print("/");

  Serial.print(rtc.getMonth());

  Serial.print("/");

  Serial.print(rtc.getYear());

  Serial.print(" ");
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

void print2digits(int number) {

  if (number < 10) {

    Serial.print("0");

  }

  Serial.print(number);
}

/*
項目 求值                            單位  註解
溫度 bmp.readTemperature()           *C  
氣壓 bmp.readPressure()              Pa    帕
　　 bmp.readPressure()/101325       atm   標準大氣壓
　　 bmp.readPressure()/101325*760   mmHg  毫米汞柱
　　 bmp.readPressure()/101325*76    cmHg  釐米汞柱
　　 bmp.readPressure()/100          hPa   百帕(氣象用)
高度 bmp.readAltitude(P)             公尺  可把已知海平面氣壓值填入P，可求相對高度

*/

#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
const char* ssid = "J8278"; //Your Network SSID
const char* password = "0928813308"; //Your Network Password

int val;
int ALCOHOL_SENSOR = A0; 
WiFiClient client;
unsigned long myChannelNumber = 1049007; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "QIUCLBE0AUWWSTRY"; //Your Write API Key

#define LED D1
int readValue; // variable to save channel field reading
const char * myReadAPIKey = "YOUR Read API Key";


void setup()
{
  Serial.begin(9600);
  delay(10);
  
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);

  ThingSpeak.begin(client);
  
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);  
}

void loop()
{
  float val = bmp.readTemperature();//analogRead(ALCOHOL_SENSOR); //Read Analog values and Store in val variable
  float val1 = bmp.readPressure();
  float val2 = bmp.readAltitude();
  float val3 = bmp.readSealevelPressure();
  float val4 = bmp.readAltitude(101500);
  
  Serial.println(val); //Print on Serial Monitor
  Serial.println(val1); //Print on Serial Monitor
  Serial.println(val2); //Print on Serial Monitor
  Serial.println(val3); //Print on Serial Monitor
  delay(10000);
  
  ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey); //Update in ThingSpeak
  delay(100);
  ThingSpeak.writeField(myChannelNumber, 2,val1, myWriteAPIKey);
  delay(100);
  ThingSpeak.writeField(myChannelNumber, 3,val2, myWriteAPIKey);
  delay(100);
  ThingSpeak.writeField(myChannelNumber, 4,val3, myWriteAPIKey);
  delay(100);

  readValue = ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey);
  Serial.print("readValue = "); // debugging instrument
  Serial.println(readValue);    // debugging instrument

  if ( readValue == 1){digitalWrite(LED, HIGH);}
  else{digitalWrite(LED, LOW);}

}
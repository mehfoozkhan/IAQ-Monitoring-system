/*******
 
 All the resources for this project:
 https://www.hackster.io/Aritro

*******/
#include "Arduino.h"
#include "MQ7.h"
#include <SoftwareSerial.h>
#include "dht.h"

dht DHT;

int smokeA0 = A5;
int gassleakage = A4;
#define MQ7_PIN_B1  A3
#define dht_apin A2
const int buzzer = 9;
int measurePin = A1;
int ledPower = 12;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
// Your threshold value
int sensorThres = 400;
SoftwareSerial s(5,6);
MQ7 mq7(MQ7_PIN_B1);
const int timeout = 10000;
char menuOption = 0;
long time0;
void setup() {
  
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(gassleakage, INPUT);
  pinMode(ledPower,OUTPUT);
  s.begin(9600);
  Serial.begin(9600);
}

void loop() {
  int smoke = analogRead(smokeA0);
  int gass = analogRead(gassleakage);
  int mq7Val = mq7.read();
  mq7Val = map(mq7Val, 40, 120, 0, 255);
  DHT.read11(dht_apin);
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin);
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage-0.1;

  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }

  String final_all = String(smoke)+"-"+String(gass)+"-"+String((mq7Val))+"-"+String(DHT.temperature)+"-"+String(dustDensity);
  Serial.println(final_all);
  Serial.println("--------------------------------------------");
  Serial.print("Smoke :");
  Serial.println(smoke);
  Serial.print("Gass :");
  Serial.println(gass);
  Serial.print(F("Carbon monooxide: ")); 
  Serial.println(mq7Val);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Dust Density:");
  Serial.println(dustDensity);
  Serial.println("--------------------------------------------");
  s.print(final_all);
  //writeString(final_all);
  if(DHT.temperature > 29){
    tone(buzzer, 1000);
  }
  else{
    noTone(buzzer);
  }
  // Checks if it has reached the threshold value
  delay(1000);
  noTone(buzzer);
}
void writeString(String stringData) {

  for (int i = 0; i < stringData.length(); i++)
  {
    s.write(stringData[i]);   
  }

}

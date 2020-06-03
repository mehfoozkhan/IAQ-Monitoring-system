#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include<ESP8266WiFi.h>
SoftwareSerial s(D6,D5);
const char* mqttServerName ="Haier-PC";// change computer name
IPAddress mqttServerIP;

void setup() {
s.begin(9600);
Serial.begin(9600);
WiFi.begin("project","123456789");  // add ssid and password here

  while(WiFi.status() !=WL_CONNECTED)
  {
    delay(500);
    Serial.println("Waiting for connection");
  }
  
  Serial.println("Connected...");
  delay(1000);
  if (WiFi.status() ==WL_CONNECTED)
  {
    Serial.println("Wi-Fi Connected!");
  }
  WiFi.hostByName(mqttServerName, mqttServerIP);
  delay(2000);
}
 
void loop() {
  s.write("s");
  
  
  
  if (s.available()>0)
  {
    
    Serial.println(s.readString());
    sendmessage(s.readString());
  }
 
 
}
void sendmessage(String d)
{
  int sres;
  int net;
  if (WiFi.status()==WL_CONNECTED)
  {
    HTTPClient http;
    String url="http://"+mqttServerIP.toString()+"/test.php?data="+d;
    http.begin(url);
    http.addHeader("Content-Type","text/plain");
    int httpCode=http.GET();
    String payload=http.getString();
    Serial.println("While sending I received this from server : "+payload);
    if (payload=="SUCCESS. Data written in file.")
    {
      sres=1;
    }
    else
    {
      sres=0;
    }
    http.end();
    net=1;
  }
  else
  {
    Serial.println("Internet Problem!");
    net=0;
  }
  
}

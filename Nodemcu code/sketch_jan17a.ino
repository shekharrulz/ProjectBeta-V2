
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <WebSocketServer.h>

SoftwareSerial swSer(14, 3, false, 256); 
WiFiServer server(80);
WebSocketServer webSocketServer;
String a="",b="";
char c;

const char* ssid = "ESGPi";
const char* password =  "1234512345";
void setup() {
  
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(0,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  Serial.begin(115200);
  swSer.begin(115200);
  WiFi.begin(ssid, password); 
 digitalWrite(13,HIGH);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  digitalWrite(12,HIGH);
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
 
  server.begin();
  delay(100);
}
 
void loop() {
 
  WiFiClient client = server.available();
 
  if (client.connected() && webSocketServer.handshake(client)) {
 
    String data;      
 
    while (client.connected()) {
 
      data = webSocketServer.getData();
 
      if (data.length() > 0) {
         Serial.println(data);
         if(data=="ON")
         {
         digitalWrite(5,HIGH);
         }
         if(data=="OFF")
         {
         digitalWrite(5,LOW);
         }
         if(data=="ONA")
         {
         digitalWrite(4,HIGH);
         }
         if(data=="OFFA")
         {
         digitalWrite(4,LOW);
         }
         if(data=="ONB")
         {
         digitalWrite(0,HIGH);
         }
         if(data=="OFFB")
         {
         digitalWrite(0,LOW);
         }
         if(data=="ONC")
         {
         digitalWrite(16,HIGH);
         }
         if(data=="OFFC")
         {
         digitalWrite(16,LOW);
         }
         if(data=="DATA")
         {
           while (swSer.available() > 0) {
           c=swSer.read();
           a+=c;}
           Serial.println(a);
    b=a.substring(a.indexOf("@")+1,a.indexOf("$"));
    delay(10);
    Serial.println(b);
    webSocketServer.sendData(b);
    
    
         }
         a="";
         b="";
      }
 
      delay(10); // Delay needed for receiving the data correctly
   }
 
   Serial.println("The client disconnected");
   delay(100);
  }
 
  delay(100);
}

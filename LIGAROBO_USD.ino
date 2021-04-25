// CODE FOR USD SENSOR AND MANUAL MOTION

#include <ESP8266WiFi.h>     // WiFi Library
#include <ESP8266WebServer.h>  // Server Library
ESP8266WebServer server(80);
#define WS "E.D.I.T.H"      // WiFi SSID
#define WP "qwertyas"       // WiFi Password
#define pin D7;                 // Echo Input from USD Sensor
#define pin D6;                 // Right Motor Pin 1
#define pin D5;                 // Right Motor Pin 2
#define pin D3;                 // Trigger to USD Sensor
#define pin D2;                 // Left Motor Pin 2
#define pin D1;                 // Left Motor Pin 1

const float distFactor = 0.034 / 2;                 // Factor by which time delay must be multiplied with to get distance
const float maxDistance = 50;                       // Maximum distance(in cm) that is detected
const float timeOut = maxDistance / distFactor;     // Time till which echo pin will be listened to, after that it is ignored.

void LEFT()                    // Left Code
{
  digitalWrite(D1,0);
  digitalWrite(D2,1);
  digitalWrite(D5,1);
  digitalWrite(D6,0);
  server.send(200, "text/plain", "LEFT" );
  }

void RIGHT()                   // Right Code
{
  digitalWrite(D1,1);
  digitalWrite(D2,0);
  digitalWrite(D5,0);
  digitalWrite(D6,1);
  server.send(200, "text/plain", "RIGHT" );
  }

void FORWARD()                   // Forward Code
{
  digitalWrite(D1,1);
  digitalWrite(D2,0);
  digitalWrite(D5,1);
  digitalWrite(D6,0);
  server.send(200, "text/plain", "FORWARD" );
}

void BACKWARD()                   // Backward Code
{
  digitalWrite(D1,0);
  digitalWrite(D2,1);
  digitalWrite(D5,0);
  digitalWrite(D6,1);
  server.send(200, "text/plain", "BACKWARD" );
  
}void STOP()                       // Stop Code
{
  digitalWrite(D1,0);
  digitalWrite(D2,0);
  digitalWrite(D5,0);
  digitalWrite(D6,0);
  server.send(200, "text/plain", "STOP" );
  }

void DDATA()                       // USD Sensor Code
{
  digitalWrite(D3,HIGH);                    // Activate Pin by making the voltage HIGH
  delayMicroseconds(10);
  digitalWrite(D3,LOW);                     // Deactivate Pin by making the voltage LOW
  long echoTime  = pulseIn(D7,HIGH,timeOut); // 
  float distance = echoTime * distFactor;
  
  server.send(200, "text/plain", String(distance)); // Send distance value to Server
  Serial.println("distance");
}

void CONNECT()
{
  server.send(200, "text/plain", " AT YOUR SERVICE BOSS!" );
  
}
void setup() {
pinMode(D1,OUTPUT);  // Output declaration
pinMode(D2,OUTPUT);  // Output declaration
pinMode(D3,OUTPUT);  // Output declaration
pinMode(D5,OUTPUT);  // Output declaration
pinMode(D6,OUTPUT);  // Output declaration
pinMode(D7,INPUT);   // Input declaration
  Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);
WiFi.begin(WS,WP);   // WiFi Initialisation
Serial.print("Connecting Boss");
while (WiFi.status()!=WL_CONNECTED) {
  Serial.print(".");
  delay (500);
}
Serial.println();
Serial.println("CONNECTION SUCCESFUL BOSS");
Serial.println(WiFi.localIP());
server.on("/LEFT", LEFT);        // Server Response Controls
server.on("/STOP", STOP);        // Server Response Controls
server.on("/DDATA", DDATA);      // Server Response Controls
server.on("/RIGHT", RIGHT);      // Server Response Controls
server.on("/FORWARD", FORWARD);  // Server Response Controls
server.on("/BACKWARD", BACKWARD);// Server Response Controls
server.on("/CONNECT", CONNECT);  // Server Response Controls
server.begin();                  // Activate Server
  // put your setup code here, to run once:

}

void loop(){

delay(600);
  if(WiFi.status()!=WL_CONNECTED) 
{
  digitalWrite(LED_BUILTIN,1);      // Activate LED by making the voltage HIGH
  delay(100);                       // wait for 0.1 second
  digitalWrite(LED_BUILTIN,0);      // Deactivate LED by making the voltage LOW
  delay(100);                       // wait for 0.1 second
}
else if(WiFi.status()==WL_CONNECTED) 
{
  digitalWrite(LED_BUILTIN,1);
}
  // put your main code here, to run repeatedly:
server.handleClient();              //Server handle the client
}
// I AM IRONMAN

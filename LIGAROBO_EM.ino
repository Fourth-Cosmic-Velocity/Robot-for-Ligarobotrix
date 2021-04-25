// CODE FOR ELECTROMAGNET AND MANUAL MOTION

#include <ESP8266WiFi.h>     // WiFi Library
#include <ESP8266WebServer.h>  // Server Library
ESP8266WebServer server(80);
#define WS "E.D.I.T.H"      // WiFi SSID
#define WP "qwertyas"       // WiFi Password
#define pin D7;                 // Electromagnet Activator Pin
#define pin D6;                 // Right Motor Pin 1
#define pin D5;                 // Right Motor Pin 2
#define pin D2;                 // Left Motor Pin 2
#define pin D1;                 // Left Motor Pin 1


void LEFT()
{
  digitalWrite(D1,0);
  digitalWrite(D2,1);
  digitalWrite(D5,1);
  digitalWrite(D6,0);
  server.send(200, "text/plain", "LEFT" );
  }

void RIGHT()
{
  digitalWrite(D1,1);
  digitalWrite(D2,0);
  digitalWrite(D5,0);
  digitalWrite(D6,1);
  server.send(200, "text/plain", "RIGHT" );
  }

void FORWARD()
{
  digitalWrite(D1,1);
  digitalWrite(D2,0);
  digitalWrite(D5,1);
  digitalWrite(D6,0);
  server.send(200, "text/plain", "FORWARD" );
}

void BACKWARD()
{
  digitalWrite(D1,0);
  digitalWrite(D2,1);
  digitalWrite(D5,0);
  digitalWrite(D6,1);
  server.send(200, "text/plain", "BACKWARD" );
  
}void STOP()
{
  digitalWrite(D1,0);
  digitalWrite(D2,0);
  digitalWrite(D5,0);
  digitalWrite(D6,0);
  server.send(200, "text/plain", "STOP" );
  }

void EMOFF()
{
  digitalWrite(D7,0);
  server.send(200, "text/plain", "EMOFF" );
}

void EMON()
{
  digitalWrite(D7,1);
  server.send(200, "text/plain", "EMON" );
 
}
void CONNECT()
{
  server.send(200, "text/plain", " AT YOUR SERVICE BOSS!" );
  
}
void setup() {
pinMode(D1,OUTPUT);  // Output declaration
pinMode(D2,OUTPUT);  // Output declaration
pinMode(D5,OUTPUT);  // Output declaration
pinMode(D6,OUTPUT);  // Output declaration
pinMode(D7,OUTPUT);   // Input declaration
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
server.on("/EMON", EMON);        // Server Response Controls
server.on("/EMOFF", EMOFF);      // Server Response Controls
server.on("/RIGHT", RIGHT);      // Server Response Controls
server.on("/FORWARD", FORWARD);  // Server Response Controls
server.on("/BACKWARD", BACKWARD);// Server Response Controls
server.on("/CONNECT", CONNECT);  // Server Response Controls
server.begin();                  // Activate Server
  // put your setup code here, to run once:

}

void loop(){
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

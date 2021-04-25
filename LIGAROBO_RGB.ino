// CODE FOR RGB SENSOR AND MANUAL MOTION

#include <ESP8266WiFi.h>        // WiFi Library
#include <ESP8266WebServer.h>   // Server Library
ESP8266WebServer server(80);
#define WS "E.D.I.T.H"        // WiFi SSID
#define WP "24681012"         // WiFi Password

#define pin D7;                 // RGB Sensor Output
#define pin D6;                 // Right Motor Pin 1
#define pin D5;                 // Right Motor Pin 2
#define pin D4;                 // RGB Snsor Pin S3
#define pin D3;                 // RGB Snsor Pin S2
#define pin D2;                 // Left Motor Pin 2
#define pin D1;                 // Left Motor Pin 1

int redfreq = 0;               // Initialise Red frequency variable
int greenfreq = 0;             // Initialise Red frequency variable
int bluefreq = 0;              // Initialise Red frequency variable

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
void CDATA()                       // RGB Sensor Code
{
digitalWrite(D3,LOW);        // Activate Red Colour First step
digitalWrite(D4,LOW);        // Activate Red Colour Second step
redfreq = pulseIn(D7,LOW);   // Store the Red frequency value
digitalWrite(D3,HIGH);       // Activate Green Colour First step
digitalWrite(D4,HIGH);       // Activate Green Colour Second step
greenfreq = pulseIn(D7,LOW); // Store the Red frequency value
digitalWrite(D3,LOW);        // Activate Blue Colour First step
digitalWrite(D4,HIGH);       // Activate Blue Colour Second step
bluefreq = pulseIn(D7,LOW);  // Store the Red frequency value


if(redfreq < greenfreq && redfreq < bluefreq)        // Condition check for Red
{Serial.println("RED COLOUR");
server.send(200, "text/plain", "Red Colour" );}      // send text "Red Colour" to server
else if(greenfreq <redfreq && greenfreq <  bluefreq) // Condition check for Green
{Serial.println("GREEN COLOUR");
server.send(200, "text/plain", "Green Colour" );}    // send text "Green Colour" to server
else if(bluefreq <redfreq && bluefreq < greenfreq)   // Condition check for Blue
{Serial.println("BLUE COLOUR");
server.send(200, "text/plain", "Blue Colour" );}     // send text "Blue Colour" to server
else
{Serial.println("DISENGEGED");}
}

void CONNECT()
{
  server.send(200, "text/plain", " AT YOUR SERVICE BOSS!" );
  
}
void setup() {
pinMode(D1,OUTPUT);  // Output declaration
pinMode(D2,OUTPUT);  // Output declaration
pinMode(D3,OUTPUT);  // Output declaration
pinMode(D4,OUTPUT);  // Output declaration
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
server.on("/CDATA", CDATA);      // Server Response Controls
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

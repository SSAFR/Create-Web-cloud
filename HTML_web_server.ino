#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "new_1.h"
/*#include "DHT.h" 
#define DHTPIN D2
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);*/
//#include "" //Our HTML webpage contents
//SSID and Password of your WiFi router
const char* ssid = "we21";
const char* password = "95603081";
IPAddress localIp(192,168,1,10);
IPAddress gatewayIp(255,255,255,0);
IPAddress subnet (192,168,1,1);
char temp[1300];
ESP8266WebServer server(80); //Server on port 80
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
  Serial.println("connect handle");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page*/
   //String action = server.arg("input1");
  //Serial.println(action);
  //----------RELAY1--------------- 
 if(server.argName(0)=="relay"){
      if(server.arg(0)=="on"){
   digitalWrite(D1,HIGH);
 }
 else if(server.arg(0)=="off"){
   digitalWrite(D1,LOW);
 }
 }
 //----------RELAY2--------------- 
   if(server.argName(0)=="togle"){
      if(server.arg(0)=="on"){
   digitalWrite(D1,HIGH);
   delay(1700);
   digitalWrite(D2,HIGH);
   digitalWrite(D1,LOW);
   delay(1700);
   digitalWrite(D1,HIGH);
   digitalWrite(D2,LOW);
   delay(500);
   digitalWrite(D2,HIGH);
    digitalWrite(D1,LOW);
    delay(500);
    digitalWrite(D2,LOW);
    digitalWrite(D1,LOW);
 }
  }
  
  
  
  }
  /*float T=dht.readTemperature();
  Serial.println(T);
   if (isnan(T))
   {
    Serial.print("no rate");
   }
  snprintf (temp,1300,MAIN_page,T,T);
 server.send(200, "text/html", temp); //Send web page*/
  
  //==============================================================
//                  SETUP
//==============================================================
void setup(void){
  WiFi.config(localIp, gatewayIp, subnet);
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
   Serial.begin(9600);
   //dht.begin();
    // Wait for connection
    int i;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    i++;
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/",handleRoot);      //Which routine to handle at root location
  server.onNotFound(handleNotFound);
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
     }
void handleNotFound()
{
  server.send(404,"text/html","<h1>foul!</h1>");
}

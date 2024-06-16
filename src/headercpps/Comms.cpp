#include "Arduino.h"
//#include "ShiftReg.h"
#include "Comms.h"

//#include <WiFiMulti.h>
#include <WiFi.h>
//#include <WebServer.h>
#include "SuperMon.h"

#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

#include <SPIFFS.h>



//#include "SuperMon.h" //houses pasted HTML


#define WIFI_SSID "Phone Hotspot"
#define WIFI_Password "thisisapassword"


// Constructor declaration
Conn::Conn(const char* ssid, const char* password) :
  _ssid(ssid),
  _password(password),
  _isConn(false),
  server(80) {}

  
  WebSocketsServer webSocket =WebSocketsServer(81); //start standard websocket port

  StaticJsonDocument<200> doc_tx ;
  JsonDocument doc_rx ;

void Conn::begin() {

Serial.begin(115200); //set same baud rate 
pinMode(LED_BUILTIN,OUTPUT);

WiFi.begin(WIFI_SSID,WIFI_Password);
//SPIFFS.begin(); uncomment when ready to use sppifs


//Serial.println("starting\n"); //change to printf maybe
printf("starting\n");



//WebSocketsServer webSocket =WebSocketsServer(81); //start standard websocket port

//server.serveStatic("/", SPIFFS, "/").setDefaultFile("webpage.html");// uploads the stuff in data folder i think

// Setup the web server
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {// for som reason need to speseify [this] in brakets to use the variables bc privte idk

        
// Simple HTML page
        String html = "<!DOCTYPE html>\n"
                     "<html>\n"
                     "<head>\n"
                     "<title>ESP32 Web Server</title>\n"
                     "</head>\n"
                     "<body>\n"
                     "<h1>Welcome to my ESP32 Web Server!</h1>\n"
                     "</body>\n"
                     "</html>\n";
//#define PAGE_MAIN SuperMon::PAGE_MAIN[]
        request->send(200, "text/html", PAGE_MAIN);//idk only gives error after git init, compiles/uploads fine tho

    });

    server.begin(); // Start the server
    webSocket.begin();
    webSocket.loop();

    
    //Serial.println(WiFi.localIP());
//server.on("/", SendWebsite);
  
}

//bool isConn = false;

void Conn::connStat() {
if (WiFi.status() == WL_CONNECTED && !_isConn){
  printf("connected. IP is adress\n");
  Serial.println(WiFi.localIP());

  webSocket.loop();

  digitalWrite(LED_BUILTIN,HIGH);
  _isConn=true;


  // String JsonString = "";
  // JsonObject objtext = doc_tx.to<JsonObject>();





};

if (WiFi.status() != WL_CONNECTED){
  printf("Connecting...\n");
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  delay(1000);
  _isConn=false;
}

};

void Conn::Comms(){

  String JsonString = "";
  JsonObject objtext = doc_tx.to<JsonObject>();
}
void Conn::webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length) {      // the parameters of this callback function are always the same -> num: id of the client who send the event, type: type of message, payload: actual data sent and length: length of payload
  switch (type) {                                     // switch on the type of information sent
    case WStype_DISCONNECTED:                         // if a client is disconnected, then type == WStype_DISCONNECTED
      Serial.println("Client " + String(num) + " disconnected");
      break;
    case WStype_CONNECTED:                            // if a client is connected, then type == WStype_CONNECTED
      Serial.println("Client " + String(num) + " connected");

    // sendJson("selectedValue", String(selected));  //idk why no work
    // sendJson("slider1val", String(slider1));
    // sendJson();


    break;

     case WStype_TEXT:                                 // if a client has sent data, then type == WStype_TEXT
      // try to decipher the JSON string received
      StaticJsonDocument<200> doc;                    // create JSON container 
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

      else {

         const char* l_type = doc["type"];
        const int l_value = doc["value"];
        Serial.println("Type: " + String(l_type));
        Serial.println("Value: " + String(l_value));

        // if LED_intensity value is received -> update and write to LED
        if(String(l_type) == "LED_intensity") {
          slider1 = int(l_value);
          //sendJson("LED_intensity", String(l_value));
           }
        // else if LED_select is changed -> switch on LED and switch off the rest
        if(String(l_type) == "LED_selected") {
          selected = int(l_value);
          //sendJson("LED_selected", String(l_value));
          
        }
      }
      Serial.println("");
      break;



      }

  }
  //}

//  void Sendinfo::Sendinfo(){

// }
#ifndef COMMS_H
#define COMMS_H

#include "Arduino.h"
//#include "ShiftReg.h"
#include "Comms.h"

#include <WiFiMulti.h>
#include <WiFi.h>
//#include <WebServer.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>


class Conn{

    

    public:

    Conn(const char* ssid, const char* password);

    void begin();
    
    void connStat();
AsyncWebServer server; // Declare the server as a member

    void Comms();
    void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length);

    private:

    bool _isConn;
    const char* _ssid;
    const char* _password;

   uint8_t selected ;
   uint8_t slider1;
   uint8_t slider2;
   uint8_t slider3;
    

};





class Sendinfo{ //creating/definig the sstuff for websockets to recive and send 


    public:

    Sendinfo(const char);

    private:



};





#endif
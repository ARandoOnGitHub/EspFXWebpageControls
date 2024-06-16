

// //blinking test
// void setup(){
//   pinMode (BUILTIN_LED, OUTPUT);
// }

// void loop() {


// delay(1000);

// digitalWrite(LED_BUILTIN,HIGH);
// delay(1000);
// digitalWrite(LED_BUILTIN,LOW);

// }





//////////////////////////OG wifi conect test code
#include <Arduino.h>
//#include <WiFiMulti.h>
#include <WiFi.h>
//#include <WebServer.h> //now using ESPAsyncWebserver
#include <ESPAsyncWebserver.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

//#include "SuperMon.h" //houses pasted HTML //now planning on using SPIFFS
 //#include <WiFiClientSecure.h> //idk wont compile without but now does???


#include "ShiftReg.h" //just created this header, defines shift selecting with shift refister for selector switch replacement, will work on it
#include "Comms.h" //created to handle wifi/server communications, will add to it later 





#define WIFI_SSID "Phone Hotspot"
#define WIFI_Password "thisisapassword"
//harcoding credentials for debuging

/*
void setup() {

Serial.begin(9600);
pinMode(LED_BUILTIN,OUTPUT);

WiFi.begin(WIFI_SSID,WIFI_Password);
Serial.println("starting\n");

Serial.println(WiFi.localIP());




  
}

bool isConn = false;

void loop() {
if (WiFi.status() == WL_CONNECTED && !isConn){
  Serial.println("connected");
  digitalWrite(LED_BUILTIN,HIGH);
  isConn=true;
}

if (WiFi.status() != WL_CONNECTED){
  Serial.println("Connecting...");
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  delay(1000);
  isConn=false;
}

}
*/
////////////////////////// check if shifting possible OG code

#define DATA_PIN 23   // DS pin of 74HC595
#define CLOCK_PIN 22  // SH_CP pin of 74HC595
#define LATCH_PIN 21  // ST_CP pin of 74HC595

// // Function to send data to the 74HC595 shift register
// void shiftOutData(uint8_t data) {
//   // Set latch pin LOW to start sending data
//   digitalWrite(LATCH_PIN, LOW);

//   // Shift out the 8 bits of data
//   shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, data);

//   // Set latch pin HIGH to output the data
//   digitalWrite(LATCH_PIN, HIGH);
// }

// void setup() {
//   // Initialize the pin modes
//   pinMode(DATA_PIN, OUTPUT);
//   pinMode(CLOCK_PIN, OUTPUT);
//   pinMode(LATCH_PIN, OUTPUT);



//   // Start with all LEDs off
//   shiftOutData(0);

//   // Begin Serial communication at 115200 baud
//   Serial.begin(115200);
//   Serial.println("Enter LED position (0-7) to turn on:");
// }

ShiftRegister shiftingOut(DATA_PIN, CLOCK_PIN, LATCH_PIN);
Conn Connetion(WIFI_SSID,WIFI_Password);

void setup(){
shiftingOut.begin();
//shiftingOut.setOutput(1);

Connetion.begin();
Serial.println(WiFi.localIP());//kinda redundent bc declared in comms

Serial.begin(115200);// kinda redundant bc declaerd in Comms
printf("Enter Output position (0-7) to turn on:\n");// temporary sainity check
//Serial.println("Enter Output position (0-7) to turn on:");// temporary sainity check
//Serial.println(WiFi.localIP());//kinda redundent bc declared in comms

  
}




void loop() {
  Connetion.connStat();
  
  // Check if data is available on the Serial port
  if (Serial.available() > 0) {
    // Read the input as an integer
    uint8_t Position = Serial.parseInt();
    uint8_t fx = 0b1000; //using 4th bit to trigger pin 13 on the fv-1 to swittch between internal and ecternal fx, will eventualy be toggled by web

    
    //OG shifting code
    // // Ensure the input is within the valid range (0-7)
    // if (ledPosition >= 0 && ledPosition <= 7) {
    //   // Turn on the specified LED
    //   // shiftOutData(0);
    //   // delay(100);
    //   shiftOutData(1 << ledPosition); //shift 1 by given ledPosition
    //   Serial.print("LED ");
    //   Serial.print(ledPosition);
    //   Serial.println(" is now ON.");
    // } else {
    //   Serial.println("Invalid input. Please enter a number between 0 and 7.");
    // }

    if(Position >=0 && Position<=7){

      shiftingOut.setOutput(Position+fx);
        // Serial.print("LED ");
        // Serial.print(Position);
        // Serial.println(" is now ON.");
        printf("Position %i is now ON \n", Position);
        }

      else{
        //Serial.print("fx change, Enter Num between 1-7");
        printf("fx change, Enter Num between 1-7\n");
        fx = fx ^ 0b1000; //flips bit 4 to triger interal fx if num>7 //was wrking b4 idk why not now
      shiftingOut.setOutput(fx);// flips bit and resets to default fx 0
      }




    // Clear the Serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}

void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t legnth){      // the parameters of this callback function are always the same -> num: id of the client who send the event, type: type of message, payload: actual data sent and length: length of payload
  switch (type) {                                     // switch on the type of information sent
    case WStype_DISCONNECTED:                         // if a client is disconnected, then type == WStype_DISCONNECTED
      printf("Client %d disconnected\n", num);
      break;
    case WStype_CONNECTED:                            // if a client is connected, then type == WStype_CONNECTED
      printf("Client %d connected\n", num);

      //sendJson()


      break;
      case WStype_TEXT:                                 // if a client has sent data, then type == WStype_TEXT
      // try to decipher the JSON string received
      StaticJsonDocument<200> doc;                    // create JSON container 
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        // Serial.print(F("deserializeJson() failed: "));
        // Serial.println(error.f_str());
        printf("deserializeJson() failed: %s\n", error.f_str());
        return;
      }

      else {
        //json string recived correctly and can be retrived 
        


      }


  }
};






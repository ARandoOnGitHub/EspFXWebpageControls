#ifndef SHIFTREG_H
#define SHIFTREG_H

#include "Arduino.h"

class ShiftRegister{

// #define dataPin 23
// #define clockPin 22
// #define latchPin 21

public:
    ShiftRegister(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin);
    void begin(){
      pinMode(dataPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(latchPin, OUTPUT);
      setOutput(1);
    
    
    
    
    
    
    };
    //void setLed(uint8_t ledPosition);
    void setOutput(uint8_t data);

private:
    uint8_t dataPin;
    uint8_t clockPin;
    uint8_t latchPin;
   
};
#endif

// public:
// //subject to change
// #define DATA_PIN 23   // DS pin of 74HC595
// #define CLOCK_PIN 22  // SH_CP pin of 74HC595
// #define LATCH_PIN 21  // ST_CP pin of 74HC595






// void shiftOutData(uint8_t data) {


//   pinMode(DATA_PIN, OUTPUT);
//   pinMode(CLOCK_PIN, OUTPUT);
//   pinMode(LATCH_PIN, OUTPUT);

//   // Set latch pin LOW to start sending data
//   digitalWrite(LATCH_PIN, LOW);

//   // Shift out the 8 bits of data
//   shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, data);

//   // Set latch pin HIGH to output the data
//   digitalWrite(LATCH_PIN, HIGH);
// }

// };


// #endif






#include "ShiftReg.h"
#include "Arduino.h"

// #define dataPin 23
// #define clockPin 22
// #define latchPin 21

    // uint8_t _dataPin;
    // uint8_t _clockPin;
    // uint8_t _latchPin;

ShiftRegister::ShiftRegister(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin) {
    // _dataPin = dataPin;
    // _clockPin = clockPin;
    // _latchPin = latchPin;
    this->dataPin = dataPin;
    this->clockPin = clockPin;
    this->latchPin = latchPin;
}

// void ShiftRegister::begin() {
//     pinMode(dataPin, OUTPUT);
//     pinMode(clockPin, OUTPUT);
//     pinMode(latchPin, OUTPUT);
// }


void ShiftRegister::setOutput(uint8_t data) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, data);
    digitalWrite(latchPin, HIGH);
}

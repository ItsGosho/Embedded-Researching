//
// Created by Gosho on 02-Jun-21.
//

#include "CustomLiquidCrystal.h"
#include "Arduino.h"

CustomLiquidCrystal::CustomLiquidCrystal(byte registerSyncPinNumber,
                                         byte enablePinNumber,
                                         byte dataBus7PinNumber,
                                         byte dataBus6PinNumber,
                                         byte dataBus5PinNumber,
                                         byte dataBus4PinNumber) : registerSyncPinNumber(registerSyncPinNumber),
                                                                   enablePinNumber(enablePinNumber),
                                                                   dataBus7PinNumber(dataBus7PinNumber),
                                                                   dataBus6PinNumber(dataBus6PinNumber),
                                                                   dataBus5PinNumber(dataBus5PinNumber),
                                                                   dataBus4PinNumber(dataBus4PinNumber) {
    pinMode(this->registerSyncPinNumber, OUTPUT);
    pinMode(this->enablePinNumber, OUTPUT);
    pinMode(this->dataBus7PinNumber, OUTPUT);
    pinMode(this->dataBus6PinNumber, OUTPUT);
    pinMode(this->dataBus5PinNumber, OUTPUT);
    pinMode(this->dataBus4PinNumber, OUTPUT);
}

CustomLiquidCrystal::CustomLiquidCrystal(byte registerSyncPinNumber,
                                         byte enablePinNumber,
                                         byte dataBus7PinNumber,
                                         byte dataBus6PinNumber,
                                         byte dataBus5PinNumber,
                                         byte dataBus4PinNumber,
                                         byte dataBus3PinNumber,
                                         byte dataBus2PinNumber,
                                         byte dataBus1PinNumber,
                                         byte dataBus0PinNumber) : registerSyncPinNumber(registerSyncPinNumber),
                                                                   enablePinNumber(enablePinNumber),
                                                                   dataBus7PinNumber(dataBus7PinNumber),
                                                                   dataBus6PinNumber(dataBus6PinNumber),
                                                                   dataBus5PinNumber(dataBus5PinNumber),
                                                                   dataBus4PinNumber(dataBus4PinNumber),
                                                                   dataBus3PinNumber(dataBus3PinNumber),
                                                                   dataBus2PinNumber(dataBus2PinNumber),
                                                                   dataBus1PinNumber(dataBus1PinNumber),
                                                                   dataBus0PinNumber(dataBus0PinNumber) {
    pinMode(this->registerSyncPinNumber, OUTPUT);
    pinMode(this->enablePinNumber, OUTPUT);
    pinMode(this->dataBus7PinNumber, OUTPUT);
    pinMode(this->dataBus6PinNumber, OUTPUT);
    pinMode(this->dataBus5PinNumber, OUTPUT);
    pinMode(this->dataBus4PinNumber, OUTPUT);
    pinMode(this->dataBus3PinNumber, OUTPUT);
    pinMode(this->dataBus2PinNumber, OUTPUT);
    pinMode(this->dataBus1PinNumber, OUTPUT);
    pinMode(this->dataBus0PinNumber, OUTPUT);
}

/*TODO: More abstract way*/
void CustomLiquidCrystal::sendCommand(byte dataBus7PinValue,
                                      byte dataBus6PinValue,
                                      byte dataBus5PinValue,
                                      byte dataBus4PinValue) {

    /*TODO: Prepare bus lines, set rs, enable, disable*/
    digitalWrite(this->dataBus7PinNumber, dataBus7PinValue);
    digitalWrite(this->dataBus6PinNumber, dataBus6PinValue);
    digitalWrite(this->dataBus5PinNumber, dataBus5PinValue);
    digitalWrite(this->dataBus4PinNumber, dataBus4PinValue);

    digitalWrite(this->registerSyncPinNumber, LOW); // RS Type
    digitalWrite(this->enablePinNumber, HIGH); // Set receiving on.
    delay(10);
    digitalWrite(this->enablePinNumber, LOW); // Set receiving off, pushing everything that came after on
    delay(10);
}

void CustomLiquidCrystal::sendData(byte dataBus7PinValue,
                                   byte dataBus6PinValue,
                                   byte dataBus5PinValue,
                                   byte dataBus4PinValue) {

    digitalWrite(this->registerSyncPinNumber, HIGH); // RS Type
    digitalWrite(this->enablePinNumber, HIGH); // Set receiving on.

    digitalWrite(this->dataBus7PinNumber, dataBus7PinValue);
    digitalWrite(this->dataBus6PinNumber, dataBus6PinValue);
    digitalWrite(this->dataBus5PinNumber, dataBus5PinValue);
    digitalWrite(this->dataBus4PinNumber, dataBus4PinValue);

    delay(10);
    digitalWrite(this->enablePinNumber, LOW); // Set receiving off, pushing everything that came after on
    delay(10);
}

void CustomLiquidCrystal::initialize() {
    delay(15);

    this->sendCommand(0, 0, 1, 1);

    delay(5);

    this->sendCommand(0, 0, 1, 1);

    delay(1);

    this->sendCommand(0, 0, 1, 1);


    //Set 4-bit interface
    this->sendCommand(0, 0, 1, 0);

    //Set interface data length, number of display lines, and character font
    this->sendCommand(0, 0, 1, 0);
    this->sendCommand(1, 0, 0, 0);

    //Display off
    this->sendCommand(0, 0, 0, 0);
    this->sendCommand(1, 0, 0, 0);

    //Display clear
    this->sendCommand(0, 0, 0, 0);
    this->sendCommand(0, 0, 0, 1);

    //Entry mode set
    this->sendCommand(0, 0, 0, 0);
    this->sendCommand(0, 1, 1, 0);

    //Display on
    this->sendCommand(0, 0, 0, 0);
    this->sendCommand(1, 1, 0, 0);
}

/*
 * Turn display on, because of the initialization it is in space mode
 *
 * 0000
 * 1110
 *
 *
 *
 * */

/*
 * OLD:
 *
 * delay(15);
    this->sendCommand(0, 0, 1, 0);
    delay(5);

    this->sendCommand(0, 0, 0, 0);
    this->sendCommand(1, 1, 0, 0);

    this->sendCommand(0, 0, 0, 0);
    this->sendCommand(0, 0, 0, 1);

    this->sendCommand(0, 0, 0, 0);
    this->sendCommand(0, 1, 1, 0);
 *
 * */

/*
 *
 *
    delay(15);

    this->sendCommand(0, 0, 1, 1);

    delay(5);

    this->sendCommand(0, 0, 1, 1);

    delay(1);

    this->sendCommand(0, 0, 1, 1);


    //Set 4-bit interface
    this->sendCommand(0, 0, 1, 0);

    //Set interface data length, number of display lines, and character font
    this->sendCommand(0, 0, 1, 0);
    this->sendCommand(1, 0, 0, 0);

    //Display off, cursor on, cursor blinking
    this->sendCommand(0, 0, 0, 0);
    this->sendCommand(1, 0,0,0);

    //Display clear
    this->sendCommand(0, 0, 0, 0);
    this->sendCommand(0, 0, 0, 1);

    //Entry mode set
    this->sendCommand(0, 0, 0, 0);
    this->sendCommand(0, 1, 1, 0);
 * */



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
    this->initialize();
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
    this->initialize();
}

/*TODO: More abstract way*/
void CustomLiquidCrystal::sendCommand(byte dataBus7PinNumber,
                                      byte dataBus6PinNumber,
                                      byte dataBus5PinNumber,
                                      byte dataBus4PinNumber) {
    digitalWrite(this->enablePinNumber, HIGH); // Set receiving on.
    digitalWrite(this->registerSyncPinNumber, LOW); // RS Type
    digitalWrite(this->dataBus7PinNumber, dataBus7PinNumber);
    digitalWrite(this->dataBus6PinNumber, dataBus6PinNumber);
    digitalWrite(this->dataBus5PinNumber, dataBus5PinNumber);
    digitalWrite(this->dataBus4PinNumber, dataBus4PinNumber);

    delay(1);
    digitalWrite(this->enablePinNumber, LOW); // Set receiving off, pushing everything that came after on
    delay(1);
}

void CustomLiquidCrystal::sendData(byte dataBus7PinNumber,
                                   byte dataBus6PinNumber,
                                   byte dataBus5PinNumber,
                                   byte dataBus4PinNumber) {
    digitalWrite(this->enablePinNumber, HIGH); // Set receiving on.
    digitalWrite(this->registerSyncPinNumber, HIGH); // RS Type
    digitalWrite(this->dataBus7PinNumber, dataBus7PinNumber);
    digitalWrite(this->dataBus6PinNumber, dataBus6PinNumber);
    digitalWrite(this->dataBus5PinNumber, dataBus5PinNumber);
    digitalWrite(this->dataBus4PinNumber, dataBus4PinNumber);

    delay(1);
    digitalWrite(this->enablePinNumber, LOW); // Set receiving off, pushing everything that came after on
    delay(1);
}

void CustomLiquidCrystal::initialize() {
    /*TODO:*/
}

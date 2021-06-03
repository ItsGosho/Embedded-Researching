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

    this->pinsMap[0] = {0, nullptr};
    this->pinsMap[1] = {1, nullptr};
    this->pinsMap[2] = {2, nullptr};
    this->pinsMap[3] = {3, nullptr};
    this->pinsMap[4] = {4, &(this->dataBus4PinNumber)};
    this->pinsMap[5] = {5, &(this->dataBus5PinNumber)};
    this->pinsMap[6] = {6, &(this->dataBus6PinNumber)};
    this->pinsMap[7] = {7, &(this->dataBus7PinNumber)};
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

    this->pinsMap[0] = {0, &(this->dataBus0PinNumber)};
    this->pinsMap[1] = {1, &(this->dataBus1PinNumber)};
    this->pinsMap[2] = {2, &(this->dataBus2PinNumber)};
    this->pinsMap[3] = {3, &(this->dataBus3PinNumber)};
    this->pinsMap[4] = {4, &(this->dataBus4PinNumber)};
    this->pinsMap[5] = {5, &(this->dataBus5PinNumber)};
    this->pinsMap[6] = {6, &(this->dataBus6PinNumber)};
    this->pinsMap[7] = {7, &(this->dataBus7PinNumber)};
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

/*If 11 is passed it must also work from the lowest to the highest*/
typedef struct {
    int dbPin;
    int mode;
} test;

void CustomLiquidCrystal::sendCommandNew(byte dataBusBits) {
    int fourBitSeparator = 0;

    //Collect them
    test modes[8] = {
            {this->dataBus4PinNumber, 0},
            {this->dataBus5PinNumber, 0},
            {this->dataBus6PinNumber, 0},
            {this->dataBus7PinNumber, 0},
            {this->dataBus4PinNumber, 0},
            {this->dataBus5PinNumber, 0},
            {this->dataBus6PinNumber, 0},
            {this->dataBus7PinNumber, 0},
    };

    int testCounter = 0;
    while (dataBusBits != 0) {
        byte lastBit = dataBusBits & 1;

        int dbPin = *this->pinsMap[7 - fourBitSeparator].dbPin;

        if (lastBit) {
            //digitalWrite(dbPin, HIGH);
            modes[testCounter] = {dbPin, HIGH};
        } else {
            //digitalWrite(dbPin, LOW);
            modes[testCounter] = {dbPin, LOW};
        }

        dataBusBits >>= 1;
        fourBitSeparator++;
        testCounter++;

        if (fourBitSeparator % 4 == 0)
            fourBitSeparator = 0;
    }


    if (fourBitSeparator != 0)
        for (int i = 7 - 4 - fourBitSeparator; i >= 0; i--) {

            byte* dbPinPointer = this->pinsMap[7 - fourBitSeparator].dbPin;

            if (dbPinPointer == nullptr)
                continue;

            int dbPin = *dbPinPointer;

            //digitalWrite(dbPin, LOW);
            modes[testCounter] = {dbPin, LOW};
            testCounter++;
        }


    for (int i = 7; i >= 0; i--) {

        if(i % 4 == 0) {
            digitalWrite(modes[i].dbPin, modes[i].mode);

            digitalWrite(this->registerSyncPinNumber, LOW); // RS Type
            digitalWrite(this->enablePinNumber, HIGH); // Set receiving on.
            delay(10);
            digitalWrite(this->enablePinNumber, LOW); // Set receiving off, pushing everything that came after on
            delay(10);
        }
    }

    //set them :)
}

void CustomLiquidCrystal::initialize() {
    delay(15);

    //this->sendCommandNew(0b00000011);
    this->sendCommand(0, 0, 1, 1);

    delay(5);

    //this->sendCommandNew(0b00000011);
    this->sendCommand(0, 0, 1, 1);

    delay(1);

    //this->sendCommandNew(0b00000011);
    this->sendCommand(0, 0, 1, 1);


    //Set 4-bit interface
    //this->sendCommandNew(0b00000010);
    this->sendCommand(0, 0, 1, 0);

    //Set interface data length, number of display lines, and character font
    this->sendCommandNew(0b00101000);

    //Display off
    this->sendCommandNew(0b00001000);

    //Display clear
    this->sendCommandNew(0b00000001);

    //Entry mode set
    this->sendCommandNew(0b00000110);

    //Display on
    this->sendCommandNew(0b00001100);
}

/*
 *
 *     delay(15);

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
 *
 * */



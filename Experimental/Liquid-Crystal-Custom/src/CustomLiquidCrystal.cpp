//
// Created by Gosho on 02-Jun-21.
//

#include "CustomLiquidCrystal.h"
#include "Arduino.h"

CustomLiquidCrystal::CustomLiquidCrystal(int registerSyncPinNumber,
                                         int enablePinNumber,
                                         int dataBus7PinNumber,
                                         int dataBus6PinNumber,
                                         int dataBus5PinNumber,
                                         int dataBus4PinNumber) : registerSyncPinNumber(registerSyncPinNumber),
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

    bitsPinsMap[0] = {8, this->dataBus7PinNumber};
    bitsPinsMap[1] = {7, this->dataBus6PinNumber};
    bitsPinsMap[2] = {6, this->dataBus5PinNumber};
    bitsPinsMap[3] = {5, this->dataBus4PinNumber};
    bitsPinsMap[4] = {4, this->dataBus7PinNumber};
    bitsPinsMap[5] = {3, this->dataBus6PinNumber};
    bitsPinsMap[6] = {2, this->dataBus5PinNumber};
    bitsPinsMap[7] = {1, this->dataBus4PinNumber};
}

CustomLiquidCrystal::CustomLiquidCrystal(int registerSyncPinNumber,
                                         int enablePinNumber,
                                         int dataBus7PinNumber,
                                         int dataBus6PinNumber,
                                         int dataBus5PinNumber,
                                         int dataBus4PinNumber,
                                         int dataBus3PinNumber,
                                         int dataBus2PinNumber,
                                         int dataBus1PinNumber,
                                         int dataBus0PinNumber) : registerSyncPinNumber(registerSyncPinNumber),
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

    bitsPinsMap[0] = {8, this->dataBus7PinNumber};
    bitsPinsMap[1] = {7, this->dataBus6PinNumber};
    bitsPinsMap[2] = {6, this->dataBus5PinNumber};
    bitsPinsMap[3] = {5, this->dataBus4PinNumber};
    bitsPinsMap[4] = {4, this->dataBus3PinNumber};
    bitsPinsMap[5] = {3, this->dataBus2PinNumber};
    bitsPinsMap[6] = {2, this->dataBus1PinNumber};
    bitsPinsMap[7] = {1, this->dataBus0PinNumber};
}

/*TODO: More abstract way*/
void CustomLiquidCrystal::sendCommand(int dataBus7PinValue,
                                      int dataBus6PinValue,
                                      int dataBus5PinValue,
                                      int dataBus4PinValue) {

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

void CustomLiquidCrystal::sendData(int dataBus7PinValue,
                                   int dataBus6PinValue,
                                   int dataBus5PinValue,
                                   int dataBus4PinValue) {

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

int* get8Bits(int value) {
    int* bits = new int[8]{0, 0, 0, 0, 0, 0, 0, 0};

    int reverseCounterIndex = 7;
    while (value != 0) {
        int currentBit = value & 1;

        bits[reverseCounterIndex] = currentBit;
        reverseCounterIndex--;
        value >>= 1;
    }

    return bits;
}

void CustomLiquidCrystal::sendCommandNew(int dataBusBits) {
    Serial.println("Sending command!");
    int* bits = get8Bits(dataBusBits);
    Serial.println("Got bits!");

    for (int i = 0; i < 8; ++i) {

        digitalWrite(this->bitsPinsMap[i].dbPin, *(bits + i));
        Serial.print("Pin: ");
        Serial.print(this->bitsPinsMap[i].dbPin);
        Serial.print(" Value: ");
        Serial.print(*(bits + i));
        Serial.println("");

        if (i == 3 || i == 7) {
            digitalWrite(this->registerSyncPinNumber, LOW); // RS Type
            digitalWrite(this->enablePinNumber, HIGH); // Set receiving on.
            delay(10);
            digitalWrite(this->enablePinNumber, LOW); // Set receiving off, pushing everything that came after on
            delay(10);
            Serial.println("Pushed!");
        }
    }

    Serial.println("Finished sending command!");
    delete[] bits;
    Serial.println("Deleting bits!");
}

void CustomLiquidCrystal::initialize() {
    delay(3000);

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



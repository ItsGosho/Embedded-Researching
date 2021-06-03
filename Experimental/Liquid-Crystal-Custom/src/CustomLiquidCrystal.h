//
// Created by Gosho on 02-Jun-21.
//

#ifndef CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H
#define CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H


typedef unsigned char byte;
typedef struct {
    char dbNumber;
    byte* dbPin;
} pinMap;

class CustomLiquidCrystal {

    /*TODO: Add each existing pin number here, so that it can be controlled from the library :)*/
private:
    byte registerSyncPinNumber;
    byte enablePinNumber;

    byte dataBus7PinNumber;
    byte dataBus6PinNumber;
    byte dataBus5PinNumber;
    byte dataBus4PinNumber;
    byte dataBus3PinNumber;
    byte dataBus2PinNumber;
    byte dataBus1PinNumber;
    byte dataBus0PinNumber;

    pinMap pinsMap[];


public:
    CustomLiquidCrystal(byte registerSyncPinNumber, byte enablePinNumber, byte dataBus7PinNumber,
                        byte dataBus6PinNumber, byte dataBus5PinNumber, byte dataBus4PinNumber);

    CustomLiquidCrystal(byte registerSyncPinNumber, byte enablePinNumber, byte dataBus7PinNumber,
                        byte dataBus6PinNumber, byte dataBus5PinNumber, byte dataBus4PinNumber, byte dataBus3PinNumber,
                        byte dataBus2PinNumber, byte dataBus1PinNumber, byte dataBus0PinNumber);

    void sendCommand(byte dataBus7PinValue, byte dataBus6PinValue, byte dataBus5PinValue, byte dataBus4PinValue);

    void sendCommandNew(byte dataBusBits);

    void sendData(byte dataBus7PinValue, byte dataBus6PinValuer, byte dataBus5PinValuer, byte dataBus4PinValue);

    void initialize();

    //void clearDisplay()
};


#endif //CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H

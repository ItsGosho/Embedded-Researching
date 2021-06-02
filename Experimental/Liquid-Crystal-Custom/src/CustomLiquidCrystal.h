//
// Created by Gosho on 02-Jun-21.
//

#ifndef CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H
#define CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H


typedef unsigned char byte;

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

    void initialize();

public:
    CustomLiquidCrystal(byte registerSyncPinNumber, byte enablePinNumber, byte dataBus7PinNumber,
                        byte dataBus6PinNumber, byte dataBus5PinNumber, byte dataBus4PinNumber);

    CustomLiquidCrystal(byte registerSyncPinNumber, byte enablePinNumber, byte dataBus7PinNumber,
                        byte dataBus6PinNumber, byte dataBus5PinNumber, byte dataBus4PinNumber, byte dataBus3PinNumber,
                        byte dataBus2PinNumber, byte dataBus1PinNumber, byte dataBus0PinNumber);

    void sendCommand(byte dataBus7PinNumber, byte dataBus6PinNumber, byte dataBus5PinNumber, byte dataBus4PinNumber);

    void sendData(byte dataBus7PinNumber, byte dataBus6PinNumber, byte dataBus5PinNumber, byte dataBus4PinNumber);
};


#endif //CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H

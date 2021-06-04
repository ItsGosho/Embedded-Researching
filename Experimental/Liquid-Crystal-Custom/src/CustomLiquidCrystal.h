//
// Created by Gosho on 02-Jun-21.
//

#ifndef CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H
#define CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H


typedef struct {
    char bitPos;
    int dbPin;
} bitsPinMap;

class CustomLiquidCrystal {

    /*TODO: Add each existing pin number here, so that it can be controlled from the library :)*/
private:
    int registerSyncPinNumber;
    int enablePinNumber;

    int dataBus7PinNumber;
    int dataBus6PinNumber;
    int dataBus5PinNumber;
    int dataBus4PinNumber;
    int dataBus3PinNumber;
    int dataBus2PinNumber;
    int dataBus1PinNumber;
    int dataBus0PinNumber;

    bitsPinMap bitsPinsMap[];


public:
    CustomLiquidCrystal(int registerSyncPinNumber, int enablePinNumber, int dataBus7PinNumber,
                        int dataBus6PinNumber, int dataBus5PinNumber, int dataBus4PinNumber);

    CustomLiquidCrystal(int registerSyncPinNumber, int enablePinNumber, int dataBus7PinNumber,
                        int dataBus6PinNumber, int dataBus5PinNumber, int dataBus4PinNumber, int dataBus3PinNumber,
                        int dataBus2PinNumber, int dataBus1PinNumber, int dataBus0PinNumber);

    void sendCommand(int dataBus7PinValue, int dataBus6PinValue, int dataBus5PinValue, int dataBus4PinValue);

    void sendCommandNew(int dataBusBits);
    void sendDataNew(int dataBusBits);

    void sendData(int dataBus7PinValue, int dataBus6PinValuer, int dataBus5PinValuer, int dataBus4PinValue);

    void initialize();

    void clearDisplay();
};


#endif //CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H

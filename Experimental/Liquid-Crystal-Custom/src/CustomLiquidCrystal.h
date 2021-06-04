#ifndef CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H
#define CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H

#include "RegisterSelect.h"
#include "stdint.h"

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

    void sendCommand(int dataBus7PinValue,
                     int dataBus6PinValue,
                     int dataBus5PinValue,
                     int dataBus4PinValue);

    void sendData(int dataBus7PinValue,
                  int dataBus6PinValue,
                  int dataBus5PinValue,
                  int dataBus4PinValue);

    void sendCommandNew(int dataBusBits);

    void sendDataNew(int dataBusBits);

    void sendNew(RegisterSelect registerSelect, int value);

    void initialize();

    void clearDisplay();
};


#endif //CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H

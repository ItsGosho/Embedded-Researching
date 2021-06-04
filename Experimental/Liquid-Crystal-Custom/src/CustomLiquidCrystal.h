#ifndef CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H
#define CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H

#include "RegisterSelect.h"
#include "CursorDirection.h"
#include "DisplayShift.h"
#include "Arduino.h"
#include "serialPrintF/SerialPrintF.h"

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

    void send(RegisterSelect registerSelect, int value);

    void initialize();

    void clearDisplay();

private:
    void send(RegisterSelect registerSelect,
              int dataBus7PinValue,
              int dataBus6PinValue,
              int dataBus5PinValue,
              int dataBus4PinValue);

    void set4BitInterface();

    void setDisplayOff();

    void setEntryMode(CursorDirection cursorDirection, DisplayShift displayShift);

    void setDisplayOn();

    void setFunction();
};


#endif //CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H

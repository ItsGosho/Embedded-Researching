#ifndef CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H
#define CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H

#include "enums/RegisterSelect.h"
#include "enums/CursorDirection.h"
#include "enums/DisplayShift.h"
#include "enums/CharacterFont.h"
#include "enums/InterfaceLength.h"
#include "enums/Lines.h"
#include "enums/Display.h"
#include "enums/CursorToggle.h"
#include "enums/CursorBlink.h"
#include "Arduino.h"
#include "serialPrintF/SerialPrintF.h"

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

public:
    CustomLiquidCrystal(int registerSyncPinNumber, int enablePinNumber, int dataBus7PinNumber,
                        int dataBus6PinNumber, int dataBus5PinNumber, int dataBus4PinNumber);

    CustomLiquidCrystal(int registerSyncPinNumber, int enablePinNumber, int dataBus7PinNumber,
                        int dataBus6PinNumber, int dataBus5PinNumber, int dataBus4PinNumber, int dataBus3PinNumber,
                        int dataBus2PinNumber, int dataBus1PinNumber, int dataBus0PinNumber);

    void send(RegisterSelect registerSelect, int value);

    void initialize();

    void clearDisplay();

    void setDisplayOff();

    void setDisplayOn();

private:
    void send(RegisterSelect registerSelect,
              int dataBus7PinValue,
              int dataBus6PinValue,
              int dataBus5PinValue,
              int dataBus4PinValue);

    void set4BitInterface();

    void setEntryMode(CursorDirection cursorDirection, DisplayShift displayShift);

    /**
     * Cannot be used after initialization. Eg: It has only one-time usage.
     */
    void setFunction(InterfaceLength interfaceLength, Lines lines, CharacterFont characterFont);
};


#endif //CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H

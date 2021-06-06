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
#include "string.h"

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

    Display display;
    CursorToggle cursorToggle;
    CursorBlink cursorBlink;

public:
    CustomLiquidCrystal(byte registerSyncPinNumber, byte enablePinNumber, byte dataBus7PinNumber,
                        byte dataBus6PinNumber, byte dataBus5PinNumber, byte dataBus4PinNumber);

    CustomLiquidCrystal(byte registerSyncPinNumber, byte enablePinNumber, byte dataBus7PinNumber,
                        byte dataBus6PinNumber, byte dataBus5PinNumber, byte dataBus4PinNumber, byte dataBus3PinNumber,
                        byte dataBus2PinNumber, byte dataBus1PinNumber, byte dataBus0PinNumber);

    void sendText(const String& string);

    void send(RegisterSelect registerSelect, byte value);

    void initialize();

    void clearDisplay();

    void setDisplay(Display display);

    void setDisplay(Display display, CursorToggle cursorToggle, CursorBlink cursorBlink);

    void toggleCursor(CursorToggle cursorToggle);

    void blinkCursor(CursorBlink cursorBlink);

private:
    void send(RegisterSelect registerSelect,
              byte dataBus7PinValue,
              byte dataBus6PinValue,
              byte dataBus5PinValue,
              byte dataBus4PinValue);

    void set4BitInterface();

    void setEntryMode(CursorDirection cursorDirection, DisplayShift displayShift);

    /**
     * Cannot be used after initialization. Eg: It has only one-time usage.
     */
    void setFunction(InterfaceLength interfaceLength, Lines lines, CharacterFont characterFont);

    template<typename T, size_t N>
    void CustomLiquidCrystal::getBits(byte value, T (& bits)[N]);

    void set4BitMode();
};


#endif //CLIONTESTING_CUSTOMLIQUIDCRYSTAL_H

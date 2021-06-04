#include "CustomLiquidCrystal.h"

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
}

/*TODO: More abstract way*/
void CustomLiquidCrystal::send(RegisterSelect registerSelect,
                               int dataBus7PinValue,
                               int dataBus6PinValue,
                               int dataBus5PinValue,
                               int dataBus4PinValue) {

    /*TODO: Prepare bus lines, set rs, enable, disable*/
    digitalWrite(this->dataBus7PinNumber, dataBus7PinValue);
    digitalWrite(this->dataBus6PinNumber, dataBus6PinValue);
    digitalWrite(this->dataBus5PinNumber, dataBus5PinValue);
    digitalWrite(this->dataBus4PinNumber, dataBus4PinValue);

    digitalWrite(this->registerSyncPinNumber, static_cast<uint8_t>(registerSelect)); // RS Type
    digitalWrite(this->enablePinNumber, HIGH); // Set receiving on.
    delay(1);
    digitalWrite(this->enablePinNumber, LOW); // Set receiving off, pushing everything that came after on
    delay(1);
}

template<typename T, size_t N>
void getBits(uint8_t value, T (& bits)[N]) {

    int reverseCounterIndex = N - 1;
    while (value != 0) {
        uint8_t currentBit = value & 1;

        bits[reverseCounterIndex] = currentBit;
        reverseCounterIndex--;
        value >>= 1;
    }
}

void CustomLiquidCrystal::send(RegisterSelect registerSelect, int dataBusBits) {

    uint8_t bits[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    getBits(dataBusBits, bits);

    this->send(registerSelect, bits[0], bits[1], bits[2], bits[3]);
    this->send(registerSelect, bits[4], bits[5], bits[6], bits[7]);
}

void CustomLiquidCrystal::initialize() {
    delay(15);

    this->send(RegisterSelect::COMMAND, 0, 0, 1, 1);

    delay(5);

    this->send(RegisterSelect::COMMAND, 0, 0, 1, 1);

    delay(1);

    this->send(RegisterSelect::COMMAND, 0, 0, 1, 1);

    this->set4BitInterface();
    this->setFunction(InterfaceLength::FOUR_BIT, Lines::TWO, CharacterFont::FIVE_EIGHT);
    this->setDisplayOff();
    this->clearDisplay();
    this->setEntryMode(CursorDirection::INCREMENT, DisplayShift::NO);
    this->setDisplayOn();
}

/*TODO: Some of them must be private, because they can be executed only on initilizatin as setting data length, number of lines and so on,. Check doc again for them!*/

/*
 *
 *
 * */

void CustomLiquidCrystal::set4BitInterface() {
    this->send(RegisterSelect::COMMAND, 0, 0, 1, 0);
}

void CustomLiquidCrystal::setFunction(InterfaceLength interfaceLength, Lines lines, CharacterFont characterFont) {
    uint8_t interfaceLengthMask = static_cast<uint8_t>(interfaceLength) << 4;
    uint8_t linesMask = static_cast<uint8_t>(lines) << 3;
    uint8_t characterFontMask = static_cast<uint8_t>(characterFont) << 2;

    uint8_t commandBits = 0b00100000 | interfaceLengthMask | linesMask | characterFontMask;
    this->send(RegisterSelect::COMMAND, commandBits);
}

void CustomLiquidCrystal::setDisplayOff() {
    //this->send(RegisterSelect::COMMAND, 0b00101000);
    this->send(RegisterSelect::COMMAND, 0b00001000);
}

void CustomLiquidCrystal::clearDisplay() {
    this->send(RegisterSelect::COMMAND, 0b00000001);
}

void CustomLiquidCrystal::setEntryMode(CursorDirection cursorDirection, DisplayShift displayShift) {

    uint8_t cursorDirectionMask = static_cast<uint8_t>(cursorDirection) << 1;
    uint8_t displayShiftMask = static_cast<uint8_t>(displayShift) << 0;

    uint8_t commandBits = 0b00000100 | cursorDirectionMask | displayShiftMask;
    this->send(RegisterSelect::COMMAND, commandBits);
}

void CustomLiquidCrystal::setDisplayOn() {
    this->send(RegisterSelect::COMMAND, 0b00001100);
}


/*
void CustomLiquidCrystal::setDisplay(Display display, CursorToggle cursorToggle, CursorBlink cursorBlink) {

}*/

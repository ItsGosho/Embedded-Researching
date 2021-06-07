#include "CustomLiquidCrystal.h"

/*TODO: Default constructor to move same initialization in it and call it from these?!*/
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

    this->display = Display::OFF;
    this->cursorToggle = CursorToggle::OFF;
    this->cursorBlink = CursorBlink::OFF;
    this->cursorRow = 0;
    this->cursorColumn = 0;
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

    this->display = Display::OFF;
    this->cursorToggle = CursorToggle::OFF;
    this->cursorBlink = CursorBlink::OFF;
    this->cursorRow = 0;
    this->cursorColumn = 0;
}

/*TODO: More abstract way*/
void CustomLiquidCrystal::send(RegisterSelect registerSelect,
                               byte dataBus7PinValue,
                               byte dataBus6PinValue,
                               byte dataBus5PinValue,
                               byte dataBus4PinValue) {

    if (RegisterSelect::COMMAND == registerSelect) {

    }

    /*TODO: Prepare bus lines, set rs, enable, disable*/
    digitalWrite(this->dataBus7PinNumber, dataBus7PinValue);
    digitalWrite(this->dataBus6PinNumber, dataBus6PinValue);
    digitalWrite(this->dataBus5PinNumber, dataBus5PinValue);
    digitalWrite(this->dataBus4PinNumber, dataBus4PinValue);

    digitalWrite(this->registerSyncPinNumber, static_cast<byte>(registerSelect)); // RS Type
    digitalWrite(this->enablePinNumber, HIGH); // Set receiving on.
    delay(1);
    digitalWrite(this->enablePinNumber, LOW); // Set receiving off, pushing everything that came after on
    delay(1);
}

template<typename T, size_t N>
void CustomLiquidCrystal::getBits(byte value, T (& bits)[N]) {

    int reverseCounterIndex = N - 1;
    while (value != 0) {
        byte currentBit = value & 1;

        bits[reverseCounterIndex] = currentBit;
        reverseCounterIndex--;
        value >>= 1;
    }
}

void CustomLiquidCrystal::send(RegisterSelect registerSelect, byte dataBusBits) {

    byte bits[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    this->getBits(dataBusBits, bits);

    this->send(registerSelect, bits[0], bits[1], bits[2], bits[3]);
    this->send(registerSelect, bits[4], bits[5], bits[6], bits[7]);
}

void CustomLiquidCrystal::initialize() {
    this->set4BitMode();
    this->setFunction(InterfaceLength::FOUR_BIT, Lines::TWO, CharacterFont::FIVE_EIGHT);
    this->setDisplay(Display::OFF);
    this->clearDisplay();
    this->setEntryMode(CursorDirection::INCREMENT, DisplayShift::NO);
    this->setDisplay(Display::ON);
}

void CustomLiquidCrystal::set4BitMode() {
    delay(15);

    this->send(RegisterSelect::COMMAND, 0, 0, 1, 1);

    delay(5);

    this->send(RegisterSelect::COMMAND, 0, 0, 1, 1);

    delay(1);

    this->send(RegisterSelect::COMMAND, 0, 0, 1, 1);

    this->set4BitInterface();
}

void CustomLiquidCrystal::set4BitInterface() {
    this->send(RegisterSelect::COMMAND, 0, 0, 1, 0);
}

void CustomLiquidCrystal::setFunction(InterfaceLength interfaceLength, Lines lines, CharacterFont characterFont) {
    byte interfaceLengthMask = static_cast<byte>(interfaceLength) << 4;
    byte linesMask = static_cast<byte>(lines) << 3;
    byte characterFontMask = static_cast<byte>(characterFont) << 2;

    byte commandBits = 0b00100000 | interfaceLengthMask | linesMask | characterFontMask;
    this->send(RegisterSelect::COMMAND, commandBits);
}

void CustomLiquidCrystal::clearDisplay() {
    this->send(RegisterSelect::COMMAND, 0b00000001);
}

void CustomLiquidCrystal::setEntryMode(CursorDirection cursorDirection, DisplayShift displayShift) {

    byte cursorDirectionMask = static_cast<byte>(cursorDirection) << 1;
    byte displayShiftMask = static_cast<byte>(displayShift) << 0;

    byte commandBits = 0b00000100 | cursorDirectionMask | displayShiftMask;
    this->send(RegisterSelect::COMMAND, commandBits);
}

void CustomLiquidCrystal::setDisplay(Display display) {
    this->setDisplay(display, this->cursorToggle, this->cursorBlink);
}

/*TODO: new easy method => cursor (toggle, blink)*/
void CustomLiquidCrystal::toggleCursor(CursorToggle cursorToggle) {
    this->setDisplay(this->display, cursorToggle, this->cursorBlink);
}

void CustomLiquidCrystal::blinkCursor(CursorBlink cursorBlink) {
    this->setDisplay(this->display, this->cursorToggle, cursorBlink);
}

void CustomLiquidCrystal::setCursorPosition(int row, int column) {

    /*TODO: With bitwise!*/
    row = row > 1 ? 1 : row;
    column = column > 15 ? 15 : column;

    this->send(RegisterSelect::COMMAND, (0b10000000) | (row << 6) | column);
}

void CustomLiquidCrystal::setDisplay(Display display, CursorToggle cursorToggle, CursorBlink cursorBlink) {
    byte displayMask = static_cast<byte>(display) << 2;
    byte cursorToggleMask = static_cast<byte>(cursorToggle) << 1;
    byte cursorBlinkMask = static_cast<byte>(cursorBlink) << 0;

    byte commandBits = 0b00001000 | displayMask | cursorToggleMask | cursorBlinkMask;
    this->send(RegisterSelect::COMMAND, commandBits);

    this->display = display;
    this->cursorToggle = cursorToggle;
    this->cursorBlink = cursorBlink;
}

void CustomLiquidCrystal::sendText(const String& string) {

    for (const char& character : string) {
        this->send(RegisterSelect::DATA, character);

        /*TODO: Refactor*/
        this->cursorColumn++;

        if (this->cursorColumn > 15) {
            this->cursorColumn = 0;
            this->cursorRow++;

            if(this->cursorRow > 1) {
                this->cursorRow = 0;
            }

            this->setCursorPosition(this->cursorRow, this->cursorColumn);
        }
    }
}

void CustomLiquidCrystal::sendCharacter(const byte& characterIndex) {
    this->send(RegisterSelect::DATA, characterIndex);

    /*TODO: Refactor*/
    this->cursorColumn++;

    if (this->cursorColumn > 15) {
        this->cursorColumn = 0;
        this->cursorRow++;

        if(this->cursorRow > 1) {
            this->cursorRow = 0;
        }

        this->setCursorPosition(this->cursorRow, this->cursorColumn);
    }
}

int CustomLiquidCrystal::incrementCursorColumn() {
    //TODO: If the cursor is bigger than 15 (This will be variable, which is defined by the number of lines, each having X places)

    //TODO: Try with bitwise
    if (this->cursorColumn > 15)
        this->cursorColumn = 0;

    this->cursorColumn++;
}

void CustomLiquidCrystal::setCursorPositionByCounter() {
    /*TODO: We must note if the */
}

int CustomLiquidCrystal::getCursorRow() {
    return this->cursorRow;
}

int CustomLiquidCrystal::getCursorColumn() {
    return this->cursorColumn;
}

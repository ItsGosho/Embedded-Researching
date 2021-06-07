#include "CustomLiquidCrystal.h"

/*TODO: Default constructor to move same initialization in it and call it from these?!*/

CustomLiquidCrystal::CustomLiquidCrystal(byte registerSyncPinNumber,
                                         byte enablePinNumber,
                                         byte dataBus7PinNumber,
                                         byte dataBus6PinNumber,
                                         byte dataBus5PinNumber,
                                         byte dataBus4PinNumber) : CustomLiquidCrystal(registerSyncPinNumber,
                                                                                       enablePinNumber,
                                                                                       dataBus7PinNumber,
                                                                                       dataBus6PinNumber,
                                                                                       dataBus5PinNumber,
                                                                                       dataBus4PinNumber,
                                                                                       -1,
                                                                                       -1,
                                                                                       -1,
                                                                                       -1) {
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
    this->setCommunicationPinsToOutput();
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

template<typename T, size_t N>
void CustomLiquidCrystal::setPinsMode(T (& pinNumbers)[N], const byte& mode) {
    for (size_t i = 0; i < N; i++) {
        pinMode(pinNumbers[i], mode);
    }
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

            if (this->cursorRow > 1) {
                this->cursorRow = 0;
            }

            this->setCursorPosition(this->cursorRow, this->cursorColumn);
        }
    }
}

//TODO: Maybe we can expose by name. Hold it somewhere and internaly get the index "Smile" -> 0
void CustomLiquidCrystal::sendCharacter(const byte& characterIndex) {
    this->send(RegisterSelect::DATA, characterIndex);

    /*TODO: Refactor*/
    this->cursorColumn++;

    if (this->cursorColumn > 15) {
        this->cursorColumn = 0;
        this->cursorRow++;

        if (this->cursorRow > 1) {
            this->cursorRow = 0;
        }

        this->setCursorPosition(this->cursorRow, this->cursorColumn);
    }
}

/*
 * TODO:
 * For each create custom character, you must return back to DD-RAM, but we must somehow know the position of the cursor which it was on.
 *
 * */
//TODO: Maybe we can expose by name. Hold it somewhere and internaly get the index "Smile" -> 0
void CustomLiquidCrystal::createCustomCharacter(const byte& characterIndex, byte customCharacter[]) {

    //Check if the char index is not bigger that 8/6 depending on the size of pixels per block
    //Select the CG-RAM Index
    //customLiquidCrystal.send(RegisterSelect::COMMAND, 0b01000000);
    this->send(RegisterSelect::COMMAND, (0b01000000) | (characterIndex << 3));

    for (int i = 0; i < 8; ++i)
        this->send(RegisterSelect::DATA, customCharacter[i]);

    this->setCursorPosition(this->cursorRow, this->cursorColumn);
}

void CustomLiquidCrystal::setCommunicationPinsToOutput() {
    byte communicationPins[] = {this->registerSyncPinNumber,
                                this->enablePinNumber,
                                this->dataBus7PinNumber,
                                this->dataBus6PinNumber,
                                this->dataBus5PinNumber,
                                this->dataBus4PinNumber,
                                this->dataBus3PinNumber,
                                this->dataBus2PinNumber,
                                this->dataBus1PinNumber,
                                this->dataBus0PinNumber};

    this->setPinsMode(communicationPins, OUTPUT);
}
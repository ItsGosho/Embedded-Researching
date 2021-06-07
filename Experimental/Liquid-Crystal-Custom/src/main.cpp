#include <Arduino.h>
#include "CustomLiquidCrystal.h"
#include <avr8-stub.h>

/*
 *
 * VSS  - N/A
 * VDD  - N/A
 * V0   - N/A
 * RS   - 9
 * R/W  - N/A
 * E    - 8
 * DB0  -
 * DB1  -
 * DB2  -
 * DB3  -
 * DB4  - 5
 * DB5  - 4
 * DB6  - 3
 * DB7  - 2
 * LED+ - N/A
 * LED- - N/A
 *
 * TILT - 13
 *
 * */

CustomLiquidCrystal customLiquidCrystal(9, 8, 2, 3, 4, 5);

/*TODO: ASCII Converter when we expose setting text*/
/*TODO: To view all of the available commands and test them*/

void testCycle() {
    customLiquidCrystal.toggleCursor(CursorToggle::ON);
    delay(3000);

    customLiquidCrystal.setDisplay(Display::OFF);
    customLiquidCrystal.blinkCursor(CursorBlink::ON);

    delay(3000);

    customLiquidCrystal.setDisplay(Display::ON);

    delay(3000);

    customLiquidCrystal.clearDisplay();

    delay(3000);

    customLiquidCrystal.send(RegisterSelect::DATA, 0b01001000);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01100101);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01101100);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01101100);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01101111);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b00110010);
}

/*
 * TODO:
 * For each create custom character, you must return back to DD-RAM, but we must somehow know the position of the cursor which it was on.
 *
 * */
void createCustomCharacter(const byte& characterIndex, byte customCharacter[]) {

    //Check if the char index is not bigger that 8/6 depending on the size of pixels per block
    //Select the CG-RAM Index
    //customLiquidCrystal.send(RegisterSelect::COMMAND, 0b01000000);
    customLiquidCrystal.send(RegisterSelect::COMMAND, (0b01000000) | (characterIndex << 3));

    for (int i = 0; i < 8; ++i) {
        customLiquidCrystal.send(RegisterSelect::DATA, customCharacter[i]);
    }

    customLiquidCrystal.setCursorPosition(customLiquidCrystal.getCursorRow(), customLiquidCrystal.getCursorColumn());
}

void setup() {
    /*TODO: Move automatically into the constructor*/
    customLiquidCrystal.initialize();

    customLiquidCrystal.sendText("Hello World! This is Bulgaria :)Hello World! This is Bulgaria 2!ZZZZZZZZZZZZZZZ12");

    byte customChar[] = {
            0b00000,
            0b01010,
            0b00000,
            0b10001,
            0b01110,
            0b00000,
            0b00000,
            0b00000
    };

    createCustomCharacter(0, customChar);

    customLiquidCrystal.sendCharacter(0);
}

//1001001101
void loop() {
    int test = 1;
}
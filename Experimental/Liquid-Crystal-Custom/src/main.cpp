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

void setup() {
    customLiquidCrystal.initialize();
    /*TODO: Clear when initializing*/

    customLiquidCrystal.sendText("Joreto!");
    customLiquidCrystal.sendText(" BG");

    /*customLiquidCrystal.send(RegisterSelect::DATA, 0b01001000);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01100101);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01101100);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01101100);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01101111);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b00110010);


    customLiquidCrystal.send(RegisterSelect::DATA, 0b00100000);

    customLiquidCrystal.send(RegisterSelect::DATA, 0b00100000);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01000111);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01100101);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01101111);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01110010);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01100111);
    customLiquidCrystal.send(RegisterSelect::DATA, 0b01101001);*/
}

//1001001101
void loop() {
    int test = 1;
}
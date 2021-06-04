#include <Arduino.h>
#include "CustomLiquidCrystal.h"

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
void setup() {
    Serial.begin(9600);
    customLiquidCrystal.initialize();
    /*TODO: Clear when initializing*/

    customLiquidCrystal.sendNew(RegisterSelect::DATA, 0b01001000);
    customLiquidCrystal.sendNew(RegisterSelect::DATA, 0b01100101);
    customLiquidCrystal.sendNew(RegisterSelect::DATA, 0b01101100);
    customLiquidCrystal.sendNew(RegisterSelect::DATA, 0b01101100);
    customLiquidCrystal.sendNew(RegisterSelect::DATA, 0b01101111);
    customLiquidCrystal.sendNew(RegisterSelect::DATA, 0b00110010);
}

//1001001101
void loop() {
    int test = 1;
}
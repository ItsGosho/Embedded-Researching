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

    /*TODO: Clear when initializing*/
    delay(15);
    customLiquidCrystal.sendCommand(0, 0, 1, 0);
    delay(5);

    customLiquidCrystal.sendCommand(0, 0, 0, 0);
    customLiquidCrystal.sendCommand(1, 1, 0, 0);

    customLiquidCrystal.sendCommand(0, 0, 0, 0);
    customLiquidCrystal.sendCommand(0, 0, 0, 1);

    customLiquidCrystal.sendCommand(0, 0, 0, 0);
    customLiquidCrystal.sendCommand(0, 1, 1, 0);

    customLiquidCrystal.sendData(0,0,1,0);
    customLiquidCrystal.sendData(0,1,0,0);

    //test
    /*customLiquidCrystal.sendData(0,0,0,1);
    customLiquidCrystal.sendData(0,0,0,1);*/
}

void loop() {

}
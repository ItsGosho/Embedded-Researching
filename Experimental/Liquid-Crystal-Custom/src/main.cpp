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
    customLiquidCrystal.initialize();
    /*TODO: Clear when initializing*/

/*    customLiquidCrystal.sendCommand(0, 0, 1, 0); // Set to 4 bit operation

    //Set 4 bit operation and set one line display and 5x8
    customLiquidCrystal.sendCommand(0, 0, 1, 0);
    customLiquidCrystal.sendCommand(0, 0, 0, 0);

    //Turns on display and cursor, because of initilization it was in space mode
    customLiquidCrystal.sendCommand(0, 0, 0, 0);
    customLiquidCrystal.sendCommand(1, 1, 1, 0);

    //Set to increment address by one and shift cursor on char write
    customLiquidCrystal.sendCommand(0, 0, 0, 0);
    customLiquidCrystal.sendCommand(0, 1, 1, 0);*/

    //Write H

   /* customLiquidCrystal.sendCommand(0, 0, 0, 0); // turn on display and cursor
    customLiquidCrystal.sendCommand(1, 1, 1, 0);*/

    customLiquidCrystal.sendData(0, 1, 0, 0);
    customLiquidCrystal.sendData(1, 0, 0, 0);

    //Write d
    //customLiquidCrystal.sendData(0, 1, 1, 0);
    //customLiquidCrystal.sendData(0, 1, 0, 0);

    //delay(1500);

    //customLiquidCrystal.sendCommand(0,0,0,0);
    //customLiquidCrystal.sendCommand(0,0,0,1);

    //test
    /*customLiquidCrystal.sendData(0,0,0,1);
    customLiquidCrystal.sendData(0,0,0,1);*/
}

//1001001101
void loop() {

}
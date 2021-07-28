#ifndef KNOCK_LOCK_LCDHELPER_H
#define KNOCK_LOCK_LCDHELPER_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#define LCD_COLS 16
#define LCD_ROWS 1

class LCDHelper {

private:
    LiquidCrystal lcd;

public:
    LCDHelper(uint8_t rs, uint8_t enable,
              uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);


    void LCDHelper::writeSensorVal(const int& val);
    void LCDHelper::writeVal(char* data);
    void LCDHelper::writeVal(const char& character);
    void LCDHelper::writeVal(String data);
};

#endif //KNOCK_LOCK_LCDHELPER_H

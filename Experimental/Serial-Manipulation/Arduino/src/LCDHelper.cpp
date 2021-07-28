#include "LCDHelper.h"

LCDHelper::LCDHelper(uint8_t rs, uint8_t enable,
                     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) : lcd(rs, enable, d0, d1, d2, d3) {

    this->lcd.begin(LCD_COLS, LCD_ROWS);

}

void LCDHelper::writeSensorVal(const int& val) {
    this->lcd.clear();
    this->lcd.print(val);
}

void LCDHelper::writeVal(const char& character) {
    this->lcd.clear();
    this->lcd.print(character);
}

void LCDHelper::writeVal(char* data) {
    this->lcd.clear();
    this->lcd.print(data);
}

void LCDHelper::writeVal(String data) {
    this->lcd.clear();
    this->lcd.print(data);
}
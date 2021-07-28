#include <Arduino.h>
#include <LiquidCrystal.h>
#include "LCDHelper.h"

#define BAUD_RATE 9600
#define POTENTIOMETER_PIN A0
#define LCD_RS_PIN 7
#define LCD_EN_PIN 6
#define LCD_D0_PIN 5
#define LCD_D1_PIN 4
#define LCD_D2_PIN 3
#define LCD_D3_PIN 2

LiquidCrystal liquidCrystal(LCD_RS_PIN, LCD_EN_PIN, LCD_D0_PIN, LCD_D1_PIN, LCD_D2_PIN, LCD_D3_PIN);

void setup() {
    Serial.begin(BAUD_RATE);
    liquidCrystal.begin(LCD_COLS, LCD_ROWS);
}

void lcdWrite(char* msg) {
    liquidCrystal.clear();
    liquidCrystal.write(msg);
}

void lcdWrite(int msg) {
    liquidCrystal.clear();
    liquidCrystal.print(msg);
}

void lcdWrite(String msg) {
    liquidCrystal.clear();
    liquidCrystal.print(msg);
}

bool isSerialSynced = true;

void loop() {

 /*   for (int i = 0; i < 1000000; ++i) {
        Serial.println(i);
        delay(10);
    }*/

    /*if (Serial.available()) {
        //String data = Serial.readStringUntil('\n');
        String data = Serial.readStringUntil('\n');

        if(data == "Ready") {
            Serial.println("Ready");
            return;
        }

        //liquidCrystal.print(data);
        Serial.println(data);
    }*/

    int value = analogRead(POTENTIOMETER_PIN);
    Serial.println(value);
}
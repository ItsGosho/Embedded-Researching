#include <Arduino.h>

bool oneTime = false;

void setup() {
    Serial.begin(9600);
}

void loop() {

    int elements[42];
    if (!oneTime) {
        //delay(2000);

        pinMode(10, OUTPUT);
        digitalWrite(10, LOW);
        delay(1);

        pinMode(10, INPUT);
        delayMicroseconds(20);

        //Low response
        elements[0] = digitalRead(10);
        delayMicroseconds(80);

        //High response
        elements[1] = digitalRead(10);
        delayMicroseconds(80);

        //bits

        int indexCounter = 2;
        bool compensate = false;
        for (int i = 0; i < 40; i++) {
            int firstDelay = 50;

            if (compensate)
                firstDelay = firstDelay - 1;

            delayMicroseconds(firstDelay);

            delayMicroseconds(29);
            bool isLow = digitalRead(10) == LOW;

            if (isLow) {
                elements[indexCounter] = 0;
                compensate = true;
            } else {
                elements[indexCounter] = 1;
                delayMicroseconds(41);
                compensate = false;
            }

            indexCounter++;
        }

        oneTime = true;

        for (int i = 0; i < 42; ++i) {
            Serial.println(elements[i]);
        }
    }
}
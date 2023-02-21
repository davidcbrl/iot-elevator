#include <Arduino.h>
#include <Stepper.h>

Stepper stepper(64, 8, 10, 9, 11);
const int stepperSpeed = 500;
const int stepperStep = 64;

const int buttonUp = 12;
const int buttonDown = 13;

const int displayA = 0;
const int displayB = 1;
const int displayC = 2;
const int displayD = 3;
const int displayE = 4;
const int displayF = 5;
const int displayG = 6;
const int displayDP = 7;

int floorDistance = 64 * 40;
int currentFloor = 1;
int bluetoothAction = 0;

void displayFloor(int floor) {
    if (floor == 0) {
        digitalWrite(displayA, LOW);
        digitalWrite(displayB, LOW);
        digitalWrite(displayC, LOW);
        digitalWrite(displayD, LOW);
        digitalWrite(displayE, LOW);
        digitalWrite(displayF, LOW);
        digitalWrite(displayG, LOW);
        digitalWrite(displayDP, HIGH);
        return;
    }
    if (floor == 1) {
        digitalWrite(displayA, LOW);
        digitalWrite(displayB, HIGH);
        digitalWrite(displayC, HIGH);
        digitalWrite(displayD, LOW);
        digitalWrite(displayE, LOW);
        digitalWrite(displayF, LOW);
        digitalWrite(displayG, LOW);
        digitalWrite(displayDP, LOW);
        return;
    }
    if (floor == 2) {
        digitalWrite(displayA, HIGH);
        digitalWrite(displayB, HIGH);
        digitalWrite(displayC, LOW);
        digitalWrite(displayD, HIGH);
        digitalWrite(displayE, HIGH);
        digitalWrite(displayF, LOW);
        digitalWrite(displayG, HIGH);
        digitalWrite(displayDP, LOW);
        return;
    }
}

void setup()
{
    Serial1.begin(9600);

    stepper.setSpeed(stepperSpeed);

    pinMode(buttonUp, INPUT);
    pinMode(buttonDown, INPUT);

    pinMode(displayA, OUTPUT);
    pinMode(displayB, OUTPUT);
    pinMode(displayC, OUTPUT);
    pinMode(displayD, OUTPUT);
    pinMode(displayE, OUTPUT);
    pinMode(displayF, OUTPUT);
    pinMode(displayG, OUTPUT);
    pinMode(displayDP, OUTPUT);
}

void loop()
{
    if (Serial1.available()) {
        bluetoothAction = Serial1.read();
    }

    if (
        (digitalRead(buttonUp) == HIGH || bluetoothAction == 50)
        && (currentFloor == 1)
    ) {
        displayFloor(0);
        for (int i = 0; i < floorDistance; i += stepperStep) {
            stepper.step(stepperStep);
        }
        currentFloor = 2;
        displayFloor(currentFloor);
        Serial1.write(currentFloor);
        bluetoothAction = 0;
        delay(500);
    }

    if (
        (digitalRead(buttonDown) == HIGH || bluetoothAction == 49)
        && (currentFloor == 2)
    ) {
        displayFloor(0);
        for (int i = 0; i < floorDistance; i += stepperStep) {
            stepper.step(-stepperStep);
        }
        currentFloor = 1;
        displayFloor(currentFloor);
        Serial1.write(currentFloor);
        bluetoothAction = 0;
        delay(500);
    }
}

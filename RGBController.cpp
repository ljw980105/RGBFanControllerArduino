//
// Created by Li on 1/12/2020.
//

#include "RGBController.h"

RGBController::RGBController(int redPin, int greenPin, int bluePin) {
    this->bluePin = bluePin;
    this->redPin = redPin;
    this->greenPin = greenPin;
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void RGBController::setColor(int r, int g, int b) {
    analogWrite(redPin, r);
    analogWrite(greenPin, g);
    analogWrite(bluePin, b);
}

void RGBController::saveColor(int r, int g, int b) {
    EEPROM.write(0, r);
    EEPROM.write(1, g);
    EEPROM.write(2, b);
}

void RGBController::setSavedColor() {
    setColor(EEPROM.read(0), EEPROM.read(1), EEPROM.read(2));
}

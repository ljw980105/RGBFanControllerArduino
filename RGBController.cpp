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
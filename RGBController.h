//
// Created by Li on 1/12/2020.
//

#ifndef RGBFANCONTROLLERARDUINO_RGBCONTROLLER_H
#define RGBFANCONTROLLERARDUINO_RGBCONTROLLER_H

#include <Arduino.h>

typedef enum {
    CONTROL_MODE_STATIC,
    CONTROL_MODE_RAINBOW
} CONTROL_MODE;

class RGBController {
public:
    RGBController(int redPin, int greenPin, int bluePin);
    void setColor(int r, int g, int b);
private:
    int redPin;
    int greenPin;
    int bluePin;
};

#endif //RGBFANCONTROLLERARDUINO_RGBCONTROLLER_H

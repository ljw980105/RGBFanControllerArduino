// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!

#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
#define txPin 11
#define rxPin 10
#define FADESPEED 25     // make this higher to slow down

#include "RGBController.h"
#include <SoftwareSerial.h>

RGBController controller(REDPIN, GREENPIN, BLUEPIN);
SoftwareSerial ble(rxPin, txPin);

#pragma mark - function prototypes

void rainbow();
void setColor(char command);

#pragma mark - arduino methods

void setup() {
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    ble.begin(9600);

    controller.setColor(100, 100, 100);
}


void loop() {
    rainbow();
//    if (ble.available()) {
//        char data = ble.read();
//        setColor(data);
//        Serial.println("data received " + data);
//        
//    }
}

#pragma mark - additional methods

void setColor(char command) {
    char obtainedColor[3];
    ble.readBytes(obtainedColor, 3);
    controller.setColor(int(obtainedColor[0]),int(obtainedColor[1]),int(obtainedColor[2]));
}

void rainbow() {
    int r, g, b;

    // fade from blue to violet
    for (r = 0; r < 256; r++) {
        analogWrite(REDPIN, r);
        delay(FADESPEED);
    }
    // fade from violet to red
    for (b = 255; b > 0; b--) {
        analogWrite(BLUEPIN, b);
        delay(FADESPEED);
    }
    // fade from red to yellow
    for (g = 0; g < 256; g++) {
        analogWrite(GREENPIN, g);
        delay(FADESPEED);
    }
    // fade from yellow to green
    for (r = 255; r > 0; r--) {
        analogWrite(REDPIN, r);
        delay(FADESPEED);
    }
    // fade from green to teal
    for (b = 0; b < 256; b++) {
        analogWrite(BLUEPIN, b);
        delay(FADESPEED);
    }
    // fade from teal to blue
    for (g = 255; g > 0; g--) {
        analogWrite(GREENPIN, g);
        delay(FADESPEED);
    }
}

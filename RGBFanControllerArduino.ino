#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
#define txPin 11
#define rxPin 10
#define FADESPEED 10     // make this higher to slow down
#define FADESPEED_BREATHE 4
#define MID_DELAY 2200
#define END_DELAY 1000

#include "RGBController.h"
#include <SoftwareSerial.h>
#include <stdlib.h>

RGBController controller(REDPIN, GREENPIN, BLUEPIN);
// note that these 2 pins need to be switched when connected to the Arduino
SoftwareSerial ble(rxPin, txPin);

#pragma mark - function prototypes

void rainbow();
void staticColorWithBLE();
void triColorMode();
void rainbow_breathe();
void dualColorBreathe();
// utilities
void fadeInOutWithColor(int r, int g, int b);

#pragma mark - arduino methods

void setup() {
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    ble.begin(9600);
    Serial.begin(9600);
    controller.setSavedColor();
}


void loop() {
    //rainbow();
    //staticColorWithBLE();
    //triColorMode();
//    rainbow_breathe();
    dualColorBreathe();
}

#pragma mark - additional methods

void staticColorWithBLE() {
    if (ble.available()) {
        char data = ble.read();
        if (atoi(&data) == CONTROL_MODE_STATIC) {
            char obtainedColor[3];
            ble.readBytes(obtainedColor, 3);
            controller.setColor(int(obtainedColor[0]),int(obtainedColor[1]),int(obtainedColor[2]));
            controller.saveColor(int(obtainedColor[0]), int(obtainedColor[1]), int(obtainedColor[2]));
        }
    }
}

// orange : 253 57 1
// pink 246 10 38
// mint green: 105 255 19
void triColorMode() {
    int r = 253;
    int g = 57;
    int b = 1;
    controller.setColor(r, g, b); // orange

    // change to pink (246, 10, 38)
    while(g > 10) {
        g --;
        if (r > 246) r --;
        if (b < 38) b ++;
        controller.setColor(r, g, b);
        delay(FADESPEED);
    }
    delay(2000);

    // change to mint green (105, 255 ,19)
    while (g < 254) {
        g += 2;
        if (r > 105) r --;
        if (b > 19) b --;
        controller.setColor(r, g, b);
        delay(FADESPEED);
    }
    delay(2000);

    // change back to orange
    while(g > 57) {
        g --;
        if (r < 253) r ++;
        if (b < 19) b ++;
        controller.setColor(r, g, b);
        delay(FADESPEED);
    }
    delay(2000);
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

void rainbow_breathe() {
    fadeInOutWithColor(255, 17, 17); // red
    fadeInOutWithColor(255, 56, 0); // orange
    fadeInOutWithColor(255, 51, 22); // yellow
    fadeInOutWithColor(25, 255, 56); // mint green
    fadeInOutWithColor(0, 255, 255); // cyan blue
    fadeInOutWithColor(155, 11, 255); // purple
    fadeInOutWithColor(255, 255, 255); // white
}

void fadeInOutWithColor(int r, int g, int b) {
    RgbColor rgb;
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    HsvColor hsv = controller.RgbToHsv(rgb);
    int h = hsv.h;
    int s = hsv.s;
    int v = 0;
    while (v < hsv.v) {
        v ++;
        controller.setHSVColor(h, s, v);
        delay(FADESPEED_BREATHE);
        HsvColor hsv2;
        hsv2.h = h;
        hsv2.s = s;
        hsv2.v = v;
    }
    delay(MID_DELAY);
    while (v > 0) {
        v --;
        controller.setHSVColor(h, s, v);
        delay(FADESPEED_BREATHE);
    }
    delay(END_DELAY);
}

void dualColorBreathe() {
    // red
    fadeInOutWithColor(255, 17, 17);
    // orange
    fadeInOutWithColor(255, 56, 0);
}

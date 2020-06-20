//
// Created by Li on 1/12/2020.
//

#ifndef RGBFANCONTROLLERARDUINO_RGBCONTROLLER_H
#define RGBFANCONTROLLERARDUINO_RGBCONTROLLER_H

#include <Arduino.h>
#include <EEPROM.h>

typedef enum {
    CONTROL_MODE_STATIC,
    CONTROL_MODE_RAINBOW
} CONTROL_MODE;

typedef struct {
    unsigned int r;
    unsigned int g;
    unsigned int b;
} RgbColor;

typedef struct {
    unsigned int h;
    unsigned int s;
    unsigned char v;
} HsvColor;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} UnitHsv;

typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} UnitRGB;

class RGBController {
public:
    RGBController(int redPin, int greenPin, int bluePin);
    void setColor(int r, int g, int b);
    void saveColor(int r, int g, int b);
    void setSavedColor();
    void setRGBColor(RgbColor rgb);
    void setHSVColor(int h, int s, int v);

    RgbColor HsvToRgb(HsvColor hsv);
    HsvColor RgbToHsv(RgbColor rgb);
private:
    int redPin;
    int greenPin;
    int bluePin;

    static HsvColor unitHsvToHSv(UnitHsv hsv);
    static UnitHsv hsvToUnitHsv(HsvColor hsv);
    static RgbColor unitRGBtoRGb(UnitRGB rgb);
    static UnitRGB rgbToUnitRgb(RgbColor rgb);

};

#endif //RGBFANCONTROLLERARDUINO_RGBCONTROLLER_H

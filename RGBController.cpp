//
// Created by Li on 1/12/2020.
//

#include <math.h>
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

void RGBController::setRGBColor(RgbColor rgb) {
    setColor(rgb.r, rgb.g, rgb.b);
}

void RGBController::setHSVColor(int h, int s, int v) {
    HsvColor hsvColorOriginal;
    hsvColorOriginal.h = h;
    hsvColorOriginal.s = s;
    hsvColorOriginal.v = v;
    RgbColor rgb = HsvToRgb(hsvColorOriginal);
    setRGBColor(rgb);
}

RgbColor RGBController::HsvToRgb(HsvColor hsv) {
    UnitHsv in = hsvToUnitHsv(hsv);
    double      hh, p, q, t, ff;
    long        i;
    UnitRGB     out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return unitRGBtoRGb(out);
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
        case 0:
            out.r = in.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = in.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = in.v;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = in.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = in.v;
            break;
        case 5:
        default:
            out.r = in.v;
            out.g = p;
            out.b = q;
            break;
    }
    return unitRGBtoRGb(out);
}

HsvColor RGBController::RgbToHsv(RgbColor rgb) {
    UnitHsv out;
    double min, max, delta;
    UnitRGB in = rgbToUnitRgb(rgb);

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return unitHsvToHSv(out);
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return unitHsvToHSv(out);
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return unitHsvToHSv(out);
}

HsvColor RGBController::unitHsvToHSv(UnitHsv hsv) {
    HsvColor newHsv;
    newHsv.h = int(255.0 * (hsv.h / 360.0));
    newHsv.s = int(255.0 * hsv.s);
    newHsv.v = int(255.0 * hsv.v);
    return newHsv;
}

UnitHsv RGBController::hsvToUnitHsv(HsvColor hsv) {
    UnitHsv newHSv;
    newHSv.h = 360.0 * (double(hsv.h)/ 255.0);
    newHSv.s = (double(hsv.s)/255.0);
    newHSv.v = (double(hsv.v)/255.0);
    return newHSv;
}

RgbColor RGBController::unitRGBtoRGb(UnitRGB rgb) {
    RgbColor newRgb;
    newRgb.r = int(255.0 * rgb.r);
    newRgb.g = int(255.0 * rgb.g);
    newRgb.b = int(255.0 * rgb.b);
    return newRgb;
}

UnitRGB RGBController::rgbToUnitRgb(RgbColor rgb) {
    UnitRGB in;
    in.r = ((double)rgb.r) / 255.0;
    in.g = ((double)rgb.g) / 255.0;
    in.b = ((double)rgb.b) / 255.0;
    return in;
}

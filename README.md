# RGBFanController - Arduino

Arduino code to control rgb fans connected to an Arduino via a 12v rgb header.

I mainly followed the tutorial [here](https://learn.adafruit.com/rgb-led-strips/usage) to create the circuit.

Here's the parts list:

Part Name | Link 
--- | --- | 
Arduino Nano| https://amzn.to/2PIUIdD 
SATA to 12v dc connector | https://amzn.to/2JN7B2N 
IRLB8721 MOSFETs | https://amzn.to/2NI2mTg 
4 pin male connectors | https://amzn.to/307Lb2U 

The iOS app [here](https://github.com/ljw980105/RGBFanController-iOS) remotely controls this piece of hardware.

## Notes

When connecting the Arduino, the rx and tx pins needs to be switched.

Multithreading help:
https://arduino.stackexchange.com/questions/18538/multithreading-with-arduino
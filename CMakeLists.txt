cmake_minimum_required(VERSION 3.15)
project(RGBFanControllerArduino)

set(CMAKE_CXX_STANDARD 14)

add_executable(RGBFanControllerArduino
        .gitignore
        LICENSE
        README.md
        RGBFanControllerArduino.ino
        RGBController.cpp RGBController.h)

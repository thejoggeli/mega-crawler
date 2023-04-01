#pragma once

#include "motors/Servo.h"
#define servoSerial Serial1

class ServosManager {
private:
    ServosManager();

public:

    static ServosManager instance;

    Servo servos[16] = {
        Servo(servoSerial, 7),
        Servo(servoSerial, 8),
        Servo(servoSerial, 9),
        Servo(servoSerial, 10),
        Servo(servoSerial, 11),
        Servo(servoSerial, 12),
        Servo(servoSerial, 13),
        Servo(servoSerial, 14),
        Servo(servoSerial, 15),
        Servo(servoSerial, 16),
        Servo(servoSerial, 17),
        Servo(servoSerial, 18),
        Servo(servoSerial, 19),
        Servo(servoSerial, 20),
        Servo(servoSerial, 1),
        Servo(servoSerial, 6)
    };
    const unsigned int numServos = sizeof(servos)/sizeof(XYZrobotServo);
    
    void init();

};

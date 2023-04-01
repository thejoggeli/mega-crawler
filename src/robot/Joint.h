#ifndef __JOINT__
#define __JOINT__

#include <Arduino.h>

class Servo;

class Joint {
public:

    float angle;
    float angleOffset;
    float length;

    float minAngle = -PI*0.501f;
    float maxAngle = +PI*0.501f;

    Servo* servo;

    Joint();

    void init();

    void setServoByIndex(unsigned int idx);
    void setAngle(float angle, float seconds);

};

#endif
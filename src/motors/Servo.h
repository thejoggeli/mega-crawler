#pragma once

#include "xyzrobot/XYZrobotServo.h"

class Servo {
public:

    XYZrobotServo servo;

    Servo(Stream& stream, uint8_t id);

    void SetAngle(float angle, float seconds);

};